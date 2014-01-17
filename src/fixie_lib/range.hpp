#ifndef _FIXIE_LIB_RANGE_HPP_
#define _FIXIE_LIB_RANGE_HPP_

#include "fixie/fixie_gl_types.h"

namespace fixie
{
    class range
    {
    public:
        range();
        range(GLclampf near, GLclampf far);

        const GLclampf& near() const;
        GLclampf& near();

        const GLclampf& far() const;
        GLclampf& far();

    private:
        GLclampf _near;
        GLclampf _far;
    };

    bool operator==(const range& a, const range& b);
    bool operator!=(const range& a, const range& b);
}

#endif // _FIXIE_LIB_RANGE_HPP_
