#include "fixie_lib/fixed_point.hpp"
#include "fixie_lib/util.hpp"
#include <limits>

namespace fixie
{
    namespace priv
    {
        GLfloat default_float;
        GLfixed default_fixed;
    }

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

    real::real(GLfloat& flt)
        : _float(flt)
        , _fixed(priv::default_fixed)
        , _is_float(true)
    {
    }

    real::real(GLfixed& fxt)
        : _float(priv::default_float)
        , _fixed(fxt)
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

    GLenum real::as_enum() const
    {
        return bit_cast<GLenum>(_is_float ? _float : _fixed);
    }

    real& real::operator=(const GLfloat& flt)
    {
        if (_is_float)
        {
            _float = flt;
        }
        else
        {
            _fixed = float_to_fixed(flt);
        }
        return *this;
    }

    real& real::operator=(const GLfixed& fxt)
    {
        if (_is_float)
        {
            _float = fixed_to_float(fxt);
        }
        else
        {
            _fixed = fxt;
        }
        return *this;
    }

    const_real::const_real(const GLfloat& flt)
        : _float(flt)
        , _fixed(priv::default_fixed)
        , _is_float(true)
    {
    }

    const_real::const_real(const GLfixed& fxt)
        : _float(priv::default_float)
        , _fixed(fxt)
        , _is_float(false)
    {
    }

    GLfloat const_real::as_float() const
    {
        return _is_float ? _float : fixed_to_float(_fixed);
    }

    GLfixed const_real::as_fixed() const
    {
        return _is_float ? float_to_fixed(_float) : _fixed;
    }

    GLenum const_real::as_enum() const
    {
        return bit_cast<GLenum>(_is_float ? _float : _fixed);
    }

    real_ptr::real_ptr(GLfloat* flt)
        : _float(flt)
        , _is_float(true)
    {
    }

    real_ptr::real_ptr(GLfixed* fxt)
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

    GLenum real_ptr::as_enum(size_t n) const
    {
        return bit_cast<GLenum>(_is_float ? _float[n] : _fixed[n]);
    }

    real real_ptr::operator[](size_t n)
    {
        return _is_float ? real(_float[n]) : real(_fixed[n]);
    }

    const_real real_ptr::operator[](size_t n) const
    {
        return _is_float ? const_real(_float[n]) : const_real(_fixed[n]);
    }

    const_real_ptr::const_real_ptr(const GLfloat* flt)
        : _float(flt)
        , _is_float(true)
    {
    }

    const_real_ptr::const_real_ptr(const GLfixed* fxt)
        : _fixed(fxt)
        , _is_float(false)
    {
    }

    GLfloat const_real_ptr::as_float(size_t n) const
    {
        return _is_float ? _float[n] : fixed_to_float(_fixed[n]);
    }

    GLfixed const_real_ptr::as_fixed(size_t n) const
    {
        return _is_float ? float_to_fixed(_float[n]) : _fixed[n];
    }

    GLenum const_real_ptr::as_enum(size_t n) const
    {
        return bit_cast<GLenum>(_is_float ? _float[n] : _fixed[n]);
    }

    const_real const_real_ptr::operator[](size_t n) const
    {
        return _is_float ? const_real(_float[n]) : const_real(_fixed[n]);
    }
}
