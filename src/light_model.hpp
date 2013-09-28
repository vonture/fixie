#ifndef _LIGHT_MODEL_HPP_
#define _LIGHT_MODEL_HPP_

#include "color.hpp"
#include "fixie_gl_types.h"

namespace fixie
{
    class light_model
    {
    public:
        light_model();

        color& ambient_color();
        const color& ambient_color() const;

        GLboolean& two_sided_lighting();
        const GLboolean& two_sided_lighting() const;

    private:
        color _ambient_color;
        GLboolean _two_sided_lighting;
    };

    light_model get_default_light_model();
}

#endif // _LIGHT_MODEL_HPP_
