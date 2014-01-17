#ifndef _FIXIE_LIB_FIXED_POINT_HPP_
#define _FIXIE_LIB_FIXED_POINT_HPP_

#include <cstddef>
#include "fixie/fixie_gl_types.h"

namespace fixie
{
    GLfloat fixed_to_float(GLfixed val);
    GLfixed float_to_fixed(GLfloat val);

    class real
    {
    public:
        real(GLfloat& flt);
        real(GLfixed& fxt);

        GLfloat as_float() const;
        GLfixed as_fixed() const;
        GLenum as_enum() const;

        real& operator=(const GLfloat& flt);
        real& operator=(const GLfixed& fxt);

    private:
        GLfloat& _float;
        GLfixed& _fixed;
        bool _is_float;
    };

    class const_real
    {
    public:
        const_real(const GLfloat& flt);
        const_real(const GLfixed& fxt);

        GLfloat as_float() const;
        GLfixed as_fixed() const;
        GLenum as_enum() const;

    private:
        const GLfloat& _float;
        const GLfixed& _fixed;
        bool _is_float;
    };

    class real_ptr
    {
    public:
        real_ptr(GLfloat* flt);
        real_ptr(GLfixed* fxt);

        GLfloat as_float(size_t n) const;
        GLfixed as_fixed(size_t n) const;
        GLenum as_enum(size_t n) const;

        real operator[](size_t n);
        const_real operator[](size_t n) const;

    private:
        union
        {
            GLfloat* _float;
            GLfixed* _fixed;
        };
        bool _is_float;
    };

    class const_real_ptr
    {
    public:
        const_real_ptr(const GLfloat* flt);
        const_real_ptr(const GLfixed* fxt);

        GLfloat as_float(size_t n) const;
        GLfixed as_fixed(size_t n) const;
        GLenum as_enum(size_t n) const;

        const_real operator[](size_t n) const;

    private:
        union
        {
            const GLfloat* _float;
            const GLfixed* _fixed;
        };
        bool _is_float;
    };
}

#endif // _FIXIE_LIB_FIXED_POINT_HPP_
