#include "fixie/fixed_point.hpp"
#include <limits>

namespace fixie
{
    GLfloat fixed_to_float(GLfixed val)
    {
        GLshort int_part = static_cast<GLshort>(val >> 16);
        GLushort frac_part = static_cast<GLushort>(val & 0xFFFF);
        return int_part + static_cast<GLfloat>(frac_part) / (1 << 16);
    }

    GLfixed float_to_fixed(GLfloat val)
    {
        GLshort int_part = static_cast<GLshort>(val);
        GLushort frac_part = static_cast<GLushort>((std::numeric_limits<GLushort>::max() + 1) * val);
        return (int_part << 16) | frac_part;
    }

    real::real(GLfloat flt)
        : _float(flt)
        , _is_float(true)
    {
    }

    real::real(GLfixed fxt)
        : _fixed(fxt)
        , _is_float(false)
    {
    }

    GLfloat real::as_float() const
    {
        return _is_float ? _float : fixed_to_float(_fixed);
    }

    GLfixed real::as_fixed() const
    {
        return _is_float ? float_to_fixed(_float) : _fixed;
    }

    real_ptr::real_ptr(const GLfloat* flt)
        : _float(flt)
        , _is_float(true)
    {
    }

    real_ptr::real_ptr(const GLfixed* fxt)
        : _fixed(fxt)
        , _is_float(false)
    {
    }

    GLfloat real_ptr::as_float(size_t n) const
    {
        return _is_float ? _float[n] : fixed_to_float(_fixed[n]);
    }

    GLfixed real_ptr::as_fixed(size_t n) const
    {
        return _is_float ? float_to_fixed(_float[n]) : _fixed[n];
    }

    real real_ptr::operator[](size_t n) const
    {
        return _is_float ? real(_float[n]) : real(_fixed[n]);
    }
}
