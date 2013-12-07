#ifndef _POLYGON_STATE_HPP_
#define _POLYGON_STATE_HPP_

#include "fixie/fixie_gl_types.h"

namespace fixie
{
    class polygon_state
    {
    public:
        polygon_state();

        const GLboolean& cull_face_enabled() const;
        GLboolean& cull_face_enabled();

        const GLenum& cull_face_mode() const;
        GLenum& cull_face_mode();

        const GLenum& front_face() const;
        GLenum& front_face();

        const GLfloat& polygon_offset_factor() const;
        GLfloat& polygon_offset_factor();

        const GLfloat& polygon_offset_units() const;
        GLfloat& polygon_offset_units();

        const GLboolean& polygon_offset_fill_enabled() const;
        GLboolean& polygon_offset_fill_enabled();

    private:
        GLboolean _cull_face_enabled;
        GLenum _cull_face_mode;
        GLenum _front_face;

        GLfloat _polygon_offset_factor;
        GLfloat _polygon_offset_units;
        GLboolean _polygon_offset_fill_enabled;
    };

    polygon_state get_default_polygon_state();
}

#endif // _POLYGON_STATE_HPP_
