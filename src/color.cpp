#include "color.hpp"

namespace fixie
{
    color::color()
        : r(0.0f)
        , g(0.0f)
        , b(0.0f)
        , a(1.0f)
    {
    }

    color::color(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
        : r(red)
        , g(green)
        , b(blue)
        , a(alpha)
    {
    }

    color::color(const GLfloat data[4])
        : r(data[0])
        , g(data[1])
        , b(data[2])
        , a(data[3])
    {
    }
}
