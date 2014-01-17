#ifndef _FIXIE_LIB_RECTANGLE_HPP_
#define _FIXIE_LIB_RECTANGLE_HPP_

#include "fixie/fixie_gl_types.h"

namespace fixie
{
    class rectangle
    {
    public:
        rectangle();
        rectangle(GLint x, GLint y, GLsizei width, GLsizei height);

        const GLint& x() const;
        GLint& x();

        const GLint& y() const;
        GLint& y();

        const GLsizei& width() const;
        GLsizei& width();

        const GLsizei& height() const;
        GLsizei& height();

    private:
        GLint _x;
        GLint _y;
        GLsizei _width;
        GLsizei _height;
    };

    bool operator==(const rectangle& a, const rectangle& b);
    bool operator!=(const rectangle& a, const rectangle& b);
}

#endif // _FIXIE_LIB_RECTANGLE_HPP_
