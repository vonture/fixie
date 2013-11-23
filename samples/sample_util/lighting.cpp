#include "lighting.hpp"

#include "fixie/fixie.h"
#include "fixie/fixie_gl_es.h"

namespace sample_util
{
    light::light()
        : enabled(false)
        , ambient(construct_array(0.0f, 0.0f, 0.0f, 1.0f))
        , diffuse(construct_array(0.0f, 0.0f, 0.0f, 1.0f))
        , specular(construct_array(0.0f, 0.0f, 0.0f, 1.0f))
        , position(construct_array(0.0f, 0.0f, 1.0f, 0.0f))
        , spot_direction(construct_array(0.0f, 0.0f, -1.0f))
        , spot_exponent(1.0f)
        , spot_cutoff(180.0f)
        , constant_attenuation(0.0f)
        , linear_attenuation(0.0f)
        , quadratic_attenuation(0.0f)
    {
    }

    void sync_light(GLenum slot, const light& light)
    {
        if (light.enabled)
        {
            glEnable(slot);
            glLightfv(slot, GL_AMBIENT, light.ambient.data());
            glLightfv(slot, GL_DIFFUSE, light.diffuse.data());
            glLightfv(slot, GL_SPECULAR, light.specular.data());
            glLightfv(slot, GL_POSITION, light.position.data());
            glLightfv(slot, GL_SPOT_DIRECTION, light.spot_direction.data());
            glLightf(slot, GL_SPOT_EXPONENT, light.spot_exponent);
            glLightf(slot, GL_SPOT_CUTOFF, light.spot_cutoff);
            glLightf(slot, GL_CONSTANT_ATTENUATION, light.constant_attenuation);
            glLightf(slot, GL_LINEAR_ATTENUATION, light.linear_attenuation);
            glLightf(slot, GL_QUADRATIC_ATTENUATION, light.quadratic_attenuation);
        }
        else
        {
            glDisable(slot);
        }
    }
}
