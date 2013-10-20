#ifndef _COLOR_HPP_
#define _COLOR_HPP_

#include "fixie/fixie_gl_types.h"

#include <functional>
#include <cstddef>

namespace fixie
{
    struct color
    {
        GLfloat r, g, b, a;

        color();
        color(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
        color(const GLfloat data[4]);
    };

    bool operator==(const color& a, const color& b);
    bool operator!=(const color& a, const color& b);
}

namespace std
{
    template <>
    struct hash<fixie::color> : public std::unary_function<fixie::color, size_t>
    {
        size_t operator()(const fixie::color& key) const;
    };
}

#endif // _COLOR_HPP_
