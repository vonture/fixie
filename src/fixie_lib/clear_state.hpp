#ifndef _CLEAR_STATE_HPP_
#define _CLEAR_STATE_HPP_

#include "fixie/fixie_gl_types.h"

#include "fixie_lib/color.hpp"

namespace fixie
{
    class clear_state
    {
    public:
        clear_state();

        color& clear_color();
        const color& clear_color() const;

        GLclampf& clear_depth();
        const GLclampf& clear_depth() const;

        GLint& clear_stencil();
        const GLint& clear_stencil() const;

    private:
        color _clear_color;
        GLclampf _clear_depth;
        GLint _clear_stencil;
    };

    clear_state get_default_clear_state();
}

#endif // _CLEAR_STATE_HPP_
