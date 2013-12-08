#ifndef _HINT_STATE_HPP_
#define _HINT_STATE_HPP_

#include "fixie/fixie_gl_types.h"

namespace fixie
{
    class hint_state
    {
    public:
        hint_state();

        const GLenum& perspective_correction_hint() const;
        GLenum& perspective_correction_hint();

        const GLenum& point_smooth_hint() const;
        GLenum& point_smooth_hint();

        const GLenum& line_smooth_hint() const;
        GLenum& line_smooth_hint();

        const GLenum& fog_hint() const;
        GLenum& fog_hint();

        const GLenum& generate_mipmap_hint() const;
        GLenum& generate_mipmap_hint();

    private:
        GLenum _perspective_correction_hint;
        GLenum _point_smooth_hint;
        GLenum _line_smooth_hint;
        GLenum _fog_hint;
        GLenum _generate_mipmap_hint;
    };

    hint_state default_hint_state();
}

#endif // _HINT_STATE_HPP_
