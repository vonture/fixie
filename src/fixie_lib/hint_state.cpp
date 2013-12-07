#include "fixie_lib/hint_state.hpp"

#include "fixie/fixie_gl_es.h"

namespace fixie
{
    hint_state::hint_state()
        : _perspective_correction_hint()
        , _point_smooth_hint()
        , _line_smooth_hint()
        , _fog_hint()
        , _generate_mipmap_hint()
    {
    }

    const GLenum& hint_state::perspective_correction_hint() const
    {
        return _perspective_correction_hint;
    }

    GLenum& hint_state::perspective_correction_hint()
    {
        return _perspective_correction_hint;
    }

    const GLenum& hint_state::point_smooth_hint() const
    {
        return _point_smooth_hint;
    }

    GLenum& hint_state::point_smooth_hint()
    {
        return _point_smooth_hint;
    }

    const GLenum& hint_state::line_smooth_hint() const
    {
        return _line_smooth_hint;
    }

    GLenum& hint_state::line_smooth_hint()
    {
        return _line_smooth_hint;
    }

    const GLenum& hint_state::fog_hint() const
    {
        return _fog_hint;
    }

    GLenum& hint_state::fog_hint()
    {
        return _fog_hint;
    }

    const GLenum& hint_state::generate_mipmap_hint() const
    {
        return _generate_mipmap_hint;
    }

    GLenum& hint_state::generate_mipmap_hint()
    {
        return _generate_mipmap_hint;
    }

    fixie::hint_state get_default_hint_state()
    {
        hint_state state;
        state.perspective_correction_hint() = GL_DONT_CARE;
        state.point_smooth_hint() = GL_DONT_CARE;
        state.line_smooth_hint() = GL_DONT_CARE;
        state.fog_hint() = GL_DONT_CARE;
        state.generate_mipmap_hint() = GL_DONT_CARE;
        return state;
    }
}
