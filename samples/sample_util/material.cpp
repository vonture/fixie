#include "material.hpp"

namespace sample_util
{
    material::material()
        : ambient(construct_array(0.2f, 0.2f, 0.2f, 1.0f))
        , diffuse(construct_array(0.8f, 0.8f, 0.8f, 1.0f))
        , specular(construct_array(0.0f, 0.0f, 0.0f, 1.0f))
        , specular_exponent(0.0f)
        , emissive(construct_array(0.0f, 0.0f, 0.0f, 1.0f))
    {
    }

    void sync_material(GLenum material_face, const material& mat)
    {
        glMaterialfv(material_face, GL_AMBIENT, mat.ambient.data());
        glMaterialfv(material_face, GL_DIFFUSE, mat.diffuse.data());
        glMaterialfv(material_face, GL_SPECULAR, mat.specular.data());
        glMaterialf(material_face, GL_SHININESS, mat.specular_exponent);
        glMaterialfv(material_face, GL_EMISSION, mat.emissive.data());
    }
}
