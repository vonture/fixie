#include "fixie_lib/fog_state.hpp"

#include "fixie/fixie_gl_es.h"

namespace fixie
{
    fog_state::fog_state()
        : _fog_color()
        , _fog_density()
        , _fog_range()
        , _fog_mode()
        , _fog_enabled()
    {
    }

    const fixie::color& fog_state::fog_color() const
    {
        return _fog_color;
    }

    fixie::color& fog_state::fog_color()
    {
        return _fog_color;
    }

    const GLfloat& fog_state::fog_density() const
    {
        return _fog_density;
    }

    GLfloat& fog_state::fog_density()
    {
        return _fog_density;
    }

    const fixie::range& fog_state::fog_range() const
    {
        return _fog_range;
    }

    fixie::range& fog_state::fog_range()
    {
        return _fog_range;
    }

    const GLenum& fog_state::fog_mode() const
    {
        return _fog_mode;
    }

    GLenum& fog_state::fog_mode()
    {
        return _fog_mode;
    }

    const GLboolean& fog_state::fog_enabled() const
    {
        return _fog_enabled;
    }

    GLboolean& fog_state::fog_enabled()
    {
        return _fog_enabled;
    }

    fog_state get_default_fog_state()
    {
        fog_state state;
        state.fog_color() = color(0.0f, 0.0f, 0.0f, 0.0f);
        state.fog_density() = 1.0f;
        state.fog_range() = range(0.0f, 1.0f);
        state.fog_mode() = GL_EXP;
        state.fog_enabled() = GL_FALSE;
        return state;
    }
}