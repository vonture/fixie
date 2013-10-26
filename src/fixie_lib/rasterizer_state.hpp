#ifndef _RASTERIZER_STATE_HPP_
#define _RASTERIZER_STATE_HPP_

#include "fixie/fixie_gl_types.h"

#include "fixie_lib/rectangle.hpp"
#include "fixie_lib/range.hpp"
#include "fixie_lib/vector.hpp"

namespace fixie
{
    class rasterizer_state
    {
    public:
        rasterizer_state();

        rectangle& viewport();
        const rectangle& viewport() const;

        GLboolean& scissor_test();
        const GLboolean& scissor_test() const;

        rectangle& scissor();
        const rectangle& scissor() const;

        const GLfloat& point_size() const;
        GLfloat& point_size();

        const GLboolean& point_smooth() const;
        GLboolean& point_smooth();

        const fixie::range& point_size_range() const;
        fixie::range& point_size_range();

        const GLfloat& point_fade_threshold() const;
        GLfloat& point_fade_threshold();

        const vector3& pooint_distance_attenuation() const;
        vector3& pooint_distance_attenuation();

        const GLboolean& point_sprite() const;
        GLboolean& point_sprite();

        const GLfloat& line_width() const;
        GLfloat& line_width();

        const GLboolean& line_smooth() const;
        GLboolean& line_smooth();

        const GLboolean& cull_face() const;
        GLboolean& cull_face();

        const GLenum& cull_face_mode() const;
        GLenum& cull_face_mode();

        const GLenum& front_face() const;
        GLenum& front_face();

        const GLfloat& polygon_offset_factor() const;
        GLfloat& polygon_offset_factor();

        const GLfloat& polygon_offset_units() const;
        GLfloat& polygon_offset_units();

        const GLboolean& polygon_offset_fill() const;
        GLboolean& polygon_offset_fill();
    
    private:
        rectangle _viewport;

        GLboolean _scissor_test;
        rectangle _scissor;

        GLfloat _point_size;
        GLboolean _point_smooth;
        range _point_size_range;
        GLfloat _point_fade_threshold;
        vector3 _pooint_distance_attenuation;
        GLboolean _point_sprite;

        GLfloat _line_width;
        GLboolean _line_smooth;

        GLboolean _cull_face;
        GLenum _cull_face_mode;
        GLenum _front_face;

        GLfloat _polygon_offset_factor;
        GLfloat _polygon_offset_units;
        GLboolean _polygon_offset_fill;
    };

    rasterizer_state get_default_rasterizer_state();
}

#endif // _RASTERIZER_STATE_HPP_
