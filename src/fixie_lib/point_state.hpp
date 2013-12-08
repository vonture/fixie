#ifndef _POINT_STATE_HPP_
#define _POINT_STATE_HPP_

#include "fixie/fixie_gl_types.h"
#include "fixie_lib/range.hpp"
#include "fixie_lib/vector.hpp"

namespace fixie
{
    class point_state
    {
    public:
        point_state();

        const GLfloat& point_size() const;
        GLfloat& point_size();

        const GLboolean& point_smooth_enabled() const;
        GLboolean& point_smooth_enabled();

        const fixie::range& point_size_range() const;
        fixie::range& point_size_range();

        const GLfloat& point_fade_threshold() const;
        GLfloat& point_fade_threshold();

        const fixie::vector3& point_distance_attenuation() const;
        fixie::vector3& point_distance_attenuation();

        const GLboolean& point_sprite_enabled() const;
        GLboolean& point_sprite_enabled();

    private:
        GLfloat _point_size;
        GLboolean _point_smooth_enabled;
        range _point_size_range;
        GLfloat _point_fade_threshold;
        vector3 _point_distance_attenuation;
        GLboolean _point_sprite_enabled;
    };

    point_state default_point_state();
}

#endif // _POINT_STATE_HPP_
