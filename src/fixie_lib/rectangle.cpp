#include "fixie_lib/rectangle.hpp"

namespace fixie
{
    rectangle::rectangle()
        : _x(0)
        , _y(0)
        , _width(0)
        , _height(0)
    {
    }

    rectangle::rectangle(GLint x, GLint y, GLsizei width, GLsizei height)
        : _x(x)
        , _y(y)
        , _width(width)
        , _height(height)
    {
    }

    const GLint& rectangle::x() const
    {
        return _x;
    }

    GLint& rectangle::x()
    {
        return _x;
    }

    const GLint& rectangle::y() const
    {
        return _y;
    }

    GLint& rectangle::y()
    {
        return _y;
    }

    const GLsizei& rectangle::width() const
    {
        return _width;
    }

    GLsizei& rectangle::width()
    {
        return _width;
    }

    const GLsizei& rectangle::height() const
    {
        return _height;
    }

    GLsizei& rectangle::height()
    {
        return _height;
    }

    bool operator==(const rectangle& a, const rectangle& b)
    {
        return a.x() == b.x() &&
               a.y() == b.y() &&
               a.width() == b.width() &&
               a.height() == b.height();
    }

    bool operator!=(const rectangle& a, const rectangle& b)
    {
        return !(a == b);
    }
}
