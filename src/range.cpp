#include "range.hpp"

namespace fixie
{
    range::range()
        : near(0.0f)
        , far(1.0f)
    {
    }

    range::range(GLclampf near, GLclampf far)
        : near(near)
        , far(far)
    {
    }

    bool operator==(const range& a, const range& b)
    {
        return a.near == b.near && a.far == b.far;
    }

    bool operator!=(const range& a, const range& b)
    {
        return !(a == b);
    }
}
