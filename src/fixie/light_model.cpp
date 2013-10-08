#include "fixie/light_model.hpp"
#include "fixie/fixie_gl_es.h"

namespace fixie
{
    light_model::light_model()
        : _ambient_color()
        , _two_sided_lighting(GL_FALSE)
    {
    }

    color& light_model::ambient_color()
    {
        return _ambient_color;
    }

    const color& light_model::ambient_color() const
    {
        return _ambient_color;
    }

    GLboolean& light_model::two_sided_lighting()
    {
        return _two_sided_lighting;
    }

    const GLboolean& light_model::two_sided_lighting() const
    {
        return _two_sided_lighting;
    }

    light_model get_default_light_model()
    {
        // From the ES 1.1.12 spec, table 2.8, pg 39

        light_model material;
        material.ambient_color() = color(0.2f, 0.2f, 0.2f, 1.0f);
        material.two_sided_lighting() = GL_FALSE;
        return material;
    }
}
