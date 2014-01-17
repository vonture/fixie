#ifndef _SAMPLE_UTIL_MATERIAL_HPP_
#define _SAMPLE_UTIL_MATERIAL_HPP_

#include "vectors.hpp"

namespace sample_util
{
    typedef float4 color;

    struct material
    {
        material();

        color ambient;
        color diffuse;
        color specular;
        float specular_exponent;
        color emissive;
    };

    void sync_material(GLenum material_face, const material& mat);
}

#endif // _SAMPLE_UTIL_MATERIAL_HPP_
