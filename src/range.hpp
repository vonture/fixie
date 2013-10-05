#ifndef _RANGE_HPP_
#define _RANGE_HPP_

#include "fixie_gl_types.h"

namespace fixie
{
    struct range
    {
        GLclampf near, far;

        range();
        range(GLclampf near, GLclampf far);
    };

    bool operator==(const range& a, const range& b);
    bool operator!=(const range& a, const range& b);
}

#endif // _RANGE_HPP_
