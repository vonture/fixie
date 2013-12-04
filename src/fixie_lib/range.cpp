#include "fixie_lib/range.hpp"

namespace fixie
{
    range::range()
        : _near(0.0f)
        , _far(1.0f)
    {
    }

    range::range(GLclampf near, GLclampf far)
        : _near(near)
        , _far(far)
    {
    }

    const GLclampf& range::near() const
    {
        return _near;
    }

    GLclampf& range::near()
    {
        return _near;
    }

    const GLclampf& range::far() const
    {
        return _far;
    }

    GLclampf& range::far()
    {
        return _far;
    }

    bool operator==(const range& a, const range& b)
    {
        return a.near() == b.near() && a.far() == b.far();
    }

    bool operator!=(const range& a, const range& b)
    {
        return !(a == b);
    }
}
