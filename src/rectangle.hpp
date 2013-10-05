#ifndef _RECTANGLE_HPP_
#define _RECTANGLE_HPP_

#include "fixie_gl_types.h"

namespace fixie
{
    struct rectangle
    {
        GLint x, y;
        GLsizei width, height;

        rectangle();
        rectangle(GLint x, GLint y, GLsizei width, GLsizei height);
    };

    bool operator==(const rectangle& a, const rectangle& b);
    bool operator!=(const rectangle& a, const rectangle& b);
}

#endif // _RECTANGLE_HPP_
