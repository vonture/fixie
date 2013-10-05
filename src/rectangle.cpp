#include "rectangle.hpp"

namespace fixie
{
    rectangle::rectangle()
        : x(0)
        , y(0)
        , width(0)
        , height(0)
    {
    }

    rectangle::rectangle(GLint x, GLint y, GLsizei width, GLsizei height)
        : x(x)
        , y(y)
        , width(width)
        , height(height)
    {
    }

    bool operator==(const rectangle& a, const rectangle& b)
    {
        return a.x == b.x &&
               a.y == b.y &&
               a.width == b.width &&
               a.height == b.height;
    }

    bool operator!=(const rectangle& a, const rectangle& b)
    {
        return !(a == b);
    }
}
