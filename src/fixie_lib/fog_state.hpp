#ifndef _FOG_STATE_HPP_
#define _FOG_STATE_HPP_

#include "fixie/fixie_gl_types.h"
#include "fixie_lib/color.hpp"
#include "fixie_lib/range.hpp"

namespace fixie
{
    class fog_state
    {
    public:
        fog_state();

        const fixie::color& fog_color() const;
        fixie::color& fog_color();

        const GLfloat& fog_density() const;
        GLfloat& fog_density();

        const fixie::range& fog_range() const;
        fixie::range& fog_range();

        const GLenum& fog_mode() const;
        GLenum& fog_mode();

        const GLboolean& fog_enabled() const;
        GLboolean& fog_enabled();

    private:
        color _fog_color;
        GLfloat _fog_density;
        range _fog_range;
        GLenum _fog_mode;
        GLboolean _fog_enabled;
    };

    fog_state default_fog_state();
}

#endif // _FOG_STATE_HPP_
