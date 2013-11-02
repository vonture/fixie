#ifndef _LIGHTING_HPP_
#define _LIGHTING_HPP_

#include "vectors.hpp"

namespace sample_util
{
    typedef float4 color;

    struct light
    {
        light();

        bool enabled;

        color ambient;
        color diffuse;
        color specular;

        float4 position;

        float3 spot_direction;
        float spot_exponent;
        float spot_cutoff;

        float constant_attenuation;
        float linear_attenuation;
        float quadratic_attenuation;
    };

    void sync_light(GLenum slot, const light& light);
}

#endif // _LIGHTING_HPP_
