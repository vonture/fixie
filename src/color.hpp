#ifndef _COLOR_HPP_
#define _COLOR_HPP_

#include "fixie_gl_types.h"

namespace fixie
{
    struct color
    {
        GLfloat r, g, b, a;

        color();
        color(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
        color(const GLfloat data[4]);
    };
}

#endif // _COLOR_HPP_
