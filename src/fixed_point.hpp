#ifndef _FIXED_POINT_HPP_
#define _FIXED_POINT_HPP_

#include "fixie_gl_types.h"

namespace fixie
{
    GLfloat fixed_to_float(GLfixed val);
    GLfixed float_to_fixed(GLfloat val);

    class real
    {
    public:
        real(GLfloat flt);
        real(GLfixed fxt);

        GLfloat as_float() const;
        GLfixed as_fixed() const;

    private:
        union
        {
            GLfloat _float;
            GLfixed _fixed;
        };
        bool _is_float;
    };

    class real_ptr
    {
    public:
        real_ptr(const GLfloat* flt);
        real_ptr(const GLfixed* fxt);

        GLfloat as_float(size_t n) const;
        GLfixed as_fixed(size_t n) const;

        real operator[](size_t n) const;

    private:
        union
        {
            const GLfloat* _float;
            const GLfixed* _fixed;
        };
        bool _is_float;
    };
}

#endif // _FIXED_POINT_HPP_
