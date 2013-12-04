#include "fixie_lib/scissor_state.hpp"

#include "fixie/fixie_gl_es.h"

namespace fixie
{
    scissor_state::scissor_state()
        : _enabled()
        , _scissor()
    {
    }

    GLboolean& scissor_state::enabled()
    {
        return _enabled;
    }

    const GLboolean& scissor_state::enabled() const
    {
        return _enabled;
    }

    rectangle& scissor_state::scissor()
    {
        return _scissor;
    }

    const rectangle& scissor_state::scissor() const
    {
        return _scissor;
    }

    scissor_state get_default_scissor_state()
    {
        scissor_state state;
        state.enabled() = GL_FALSE;
        state.scissor() = rectangle(0, 0, 1, 1);
        return state;
    }
}
