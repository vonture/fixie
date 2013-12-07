#include "fixie_lib/polygon_state.hpp"

#include "fixie/fixie_gl_es.h"

namespace fixie
{
    polygon_state::polygon_state()
        : _cull_face_enabled()
        , _cull_face_mode()
        , _front_face()
        , _polygon_offset_factor()
        , _polygon_offset_units()
        , _polygon_offset_fill_enabled()
    {
    }

    const GLboolean& polygon_state::cull_face_enabled() const
    {
        return _cull_face_enabled;
    }

    GLboolean& polygon_state::cull_face_enabled()
    {
        return _cull_face_enabled;
    }

    const GLenum& polygon_state::cull_face_mode() const
    {
        return _cull_face_mode;
    }

    GLenum& polygon_state::cull_face_mode()
    {
        return _cull_face_mode;
    }

    const GLenum& polygon_state::front_face() const
    {
        return _front_face;
    }

    GLenum& polygon_state::front_face()
    {
        return _front_face;
    }

    const GLfloat& polygon_state::polygon_offset_factor() const
    {
        return _polygon_offset_factor;
    }

    GLfloat& polygon_state::polygon_offset_factor()
    {
        return _polygon_offset_factor;
    }

    const GLfloat& polygon_state::polygon_offset_units() const
    {
        return _polygon_offset_units;
    }

    GLfloat& polygon_state::polygon_offset_units()
    {
        return _polygon_offset_units;
    }

    const GLboolean& polygon_state::polygon_offset_fill_enabled() const
    {
        return _polygon_offset_fill_enabled;
    }

    GLboolean& polygon_state::polygon_offset_fill_enabled()
    {
        return _polygon_offset_fill_enabled;
    }

    polygon_state get_default_polygon_state()
    {
        polygon_state state;
        state.cull_face_enabled() = GL_FALSE;
        state.cull_face_mode() = GL_BACK;
        state.front_face() = GL_CCW;
        state.polygon_offset_factor() = 0.0f;
        state.polygon_offset_units() = 0.0f;
        state.polygon_offset_fill_enabled() = GL_FALSE;
        return state;
    }
}
