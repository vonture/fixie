#include "fixie_lib/point_state.hpp"

#include "fixie/fixie_gl_es.h"

namespace fixie
{
    point_state::point_state()
        : _point_size()
        , _point_smooth_enabled()
        , _point_size_range()
        , _point_fade_threshold()
        , _point_distance_attenuation()
        , _point_sprite_enabled()
    {
    }

    const GLfloat& point_state::point_size() const
    {
        return _point_size;
    }

    GLfloat& point_state::point_size()
    {
        return _point_size;
    }

    const GLboolean& point_state::point_smooth_enabled() const
    {
        return _point_smooth_enabled;
    }

    GLboolean& point_state::point_smooth_enabled()
    {
        return _point_smooth_enabled;
    }

    const fixie::range& point_state::point_size_range() const
    {
        return _point_size_range;
    }

    fixie::range& point_state::point_size_range()
    {
        return _point_size_range;
    }

    const GLfloat& point_state::point_fade_threshold() const
    {
        return _point_fade_threshold;
    }

    GLfloat& point_state::point_fade_threshold()
    {
        return _point_fade_threshold;
    }

    const fixie::vector3& point_state::point_distance_attenuation() const
    {
        return _point_distance_attenuation;
    }

    fixie::vector3& point_state::point_distance_attenuation()
    {
        return _point_distance_attenuation;
    }

    const GLboolean& point_state::point_sprite_enabled() const
    {
        return _point_sprite_enabled;
    }

    GLboolean& point_state::point_sprite_enabled()
    {
        return _point_sprite_enabled;
    }

    point_state default_point_state()
    {
        point_state state;
        state.point_size() = 1.0f;
        state.point_smooth_enabled() = GL_FALSE;
        state.point_size_range() = range(0.0f, 1.0f);
        state.point_fade_threshold() = 1.0f;
        state.point_distance_attenuation() = vector3(1.0f, 0.0f, 0.0f);
        state.point_sprite_enabled() = GL_FALSE;
        return state;
    }
}
