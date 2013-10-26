#include "fixie_lib/rasterizer_state.hpp"

#include "fixie/fixie_gl_es.h"

namespace fixie
{
    rasterizer_state::rasterizer_state()
        : _viewport()
        , _scissor_test()
        , _scissor()
        , _point_size()
        , _point_smooth()
        , _point_size_range()
        , _point_fade_threshold()
        , _pooint_distance_attenuation()
        , _point_sprite()
        , _line_width()
        , _line_smooth()
        , _cull_face()
        , _cull_face_mode()
        , _polygon_offset_factor()
        , _polygon_offset_units()
        , _polygon_offset_fill()
    {
    }

    rectangle& rasterizer_state::viewport()
    {
        return _viewport;
    }

    const rectangle& rasterizer_state::viewport() const
    {
        return _viewport;
    }

    GLboolean& rasterizer_state::scissor_test()
    {
        return _scissor_test;
    }

    const GLboolean& rasterizer_state::scissor_test() const
    {
        return _scissor_test;
    }

    rectangle& rasterizer_state::scissor()
    {
        return _scissor;
    }

    const rectangle& rasterizer_state::scissor() const
    {
        return _scissor;
    }

    const GLfloat& rasterizer_state::point_size() const
    {
        return _point_size;
    }

    GLfloat& rasterizer_state::point_size()
    {
        return _point_size;
    }

    const GLboolean& rasterizer_state::point_smooth() const
    {
        return _point_smooth;
    }

    GLboolean& rasterizer_state::point_smooth()
    {
        return _point_smooth;
    }

    const fixie::range& rasterizer_state::point_size_range() const
    {
        return _point_size_range;
    }

    fixie::range& rasterizer_state::point_size_range()
    {
        return _point_size_range;
    }

    const GLfloat& rasterizer_state::point_fade_threshold() const
    {
        return _point_fade_threshold;
    }

    GLfloat& rasterizer_state::point_fade_threshold()
    {
        return _point_fade_threshold;
    }

    const vector3& rasterizer_state::pooint_distance_attenuation() const
    {
        return _pooint_distance_attenuation;
    }

    vector3& rasterizer_state::pooint_distance_attenuation()
    {
        return _pooint_distance_attenuation;
    }

    const GLboolean& rasterizer_state::point_sprite() const
    {
        return _point_sprite;
    }

    GLboolean& rasterizer_state::point_sprite()
    {
        return _point_sprite;
    }

    const GLfloat& rasterizer_state::line_width() const
    {
        return _line_width;
    }

    GLfloat& rasterizer_state::line_width()
    {
        return _line_width;
    }

    const GLboolean& rasterizer_state::line_smooth() const
    {
        return _line_smooth;
    }

    GLboolean& rasterizer_state::line_smooth()
    {
        return _line_smooth;
    }

    const GLboolean& rasterizer_state::cull_face() const
    {
        return _cull_face;
    }

    GLboolean& rasterizer_state::cull_face()
    {
        return _cull_face;
    }

    const GLenum& rasterizer_state::cull_face_mode() const
    {
        return _cull_face_mode;
    }

    GLenum& rasterizer_state::cull_face_mode()
    {
        return _cull_face_mode;
    }

    const GLenum& rasterizer_state::front_face() const
    {
        return _front_face;
    }

    GLenum& rasterizer_state::front_face()
    {
        return _front_face;
    }

    const GLfloat& rasterizer_state::polygon_offset_factor() const
    {
        return _polygon_offset_factor;
    }

    GLfloat& rasterizer_state::polygon_offset_factor()
    {
        return _polygon_offset_factor;
    }

    const GLfloat& rasterizer_state::polygon_offset_units() const
    {
        return _polygon_offset_units;
    }

    GLfloat& rasterizer_state::polygon_offset_units()
    {
        return _polygon_offset_units;
    }

    const GLboolean& rasterizer_state::polygon_offset_fill() const
    {
        return _polygon_offset_fill;
    }

    GLboolean& rasterizer_state::polygon_offset_fill()
    {
        return _polygon_offset_fill;
    }

    rasterizer_state get_default_rasterizer_state()
    {
        rasterizer_state state;
        state.viewport() = rectangle(0, 0, 1, 1);
        state.scissor_test() = GL_FALSE;
        state.scissor() = rectangle(0, 0, 1, 1);
        state.point_size() = 1.0f;
        state.point_smooth() = GL_FALSE;
        state.point_size_range() = range(0.0f, 1.0f);
        state.point_fade_threshold() = 1.0f;
        state.pooint_distance_attenuation() = vector3(1.0f, 0.0f, 0.0f);
        state.point_sprite() = GL_FALSE;
        state.line_width() = 1.0f;
        state.line_smooth() = GL_FALSE;
        state.cull_face() = GL_FALSE;
        state.cull_face_mode() = GL_BACK;
        state.front_face() = GL_CCW;
        state.polygon_offset_factor() = 0.0f;
        state.polygon_offset_units() = 0.0f;
        state.polygon_offset_fill() = GL_FALSE;
        return state;
    }
}
