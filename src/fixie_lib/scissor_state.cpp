#include "fixie_lib/scissor_state.hpp"

#include "fixie/fixie_gl_es.h"

namespace fixie
{
    scissor_state::scissor_state()
        : _scissor_test_enabled()
        , _scissor()
    {
    }

    GLboolean& scissor_state::scissor_test_enabled()
    {
        return _scissor_test_enabled;
    }

    const GLboolean& scissor_state::scissor_test_enabled() const
    {
        return _scissor_test_enabled;
    }

    rectangle& scissor_state::scissor()
    {
        return _scissor;
    }

    const rectangle& scissor_state::scissor() const
    {
        return _scissor;
    }

    scissor_state default_scissor_state()
    {
        scissor_state state;
        state.scissor_test_enabled() = GL_FALSE;
        state.scissor() = rectangle(0, 0, 1, 1);
        return state;
    }
}
