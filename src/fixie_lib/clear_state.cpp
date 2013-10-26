#include "fixie_lib/clear_state.hpp"

#include "fixie/fixie_gl_es.h"

namespace fixie
{
    clear_state::clear_state()
        : _clear_color()
        , _clear_depth()
        , _clear_stencil()
    {
    }

    color& clear_state::clear_color()
    {
        return _clear_color;
    }

    const color& clear_state::clear_color() const
    {
        return _clear_color;
    }

    GLclampf& clear_state::clear_depth()
    {
        return _clear_depth;
    }

    const GLclampf& clear_state::clear_depth() const
    {
        return _clear_depth;
    }

    GLint& clear_state::clear_stencil()
    {
        return _clear_stencil;
    }

    const GLint& clear_state::clear_stencil() const
    {
        return _clear_stencil;
    }

    clear_state get_default_clear_state()
    {
        clear_state state;
        state.clear_color() = color(0.0f, 0.0f, 0.0f, 0.0f);
        state.clear_depth() = 1.0f;
        state.clear_stencil() = 0;
        return state;
    }
}
