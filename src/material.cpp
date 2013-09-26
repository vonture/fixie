#include "material.hpp"

namespace fixie
{
    material::material()
        : _ambient()
        , _diffuse()
        , _specular()
        , _emissive()
        , _specular_exponent(0.0f)
    {
    }

    color& material::ambient()
    {
        return _ambient;
    }

    const color& material::ambient() const
    {
        return _ambient;
    }

    color& material::diffuse()
    {
        return _specular;
    }

    const color& material::diffuse() const
    {
        return _specular;
    }

    color& material::specular()
    {
        return _specular;
    }

    const color& material::specular() const
    {
        return _specular;
    }

    color& material::emissive()
    {
        return _emissive;
    }

    const color& material::emissive() const
    {
        return _emissive;
    }

    GLfloat& material::specular_exponent()
    {
        return _specular_exponent;
    }

    const GLfloat& material::specular_exponent() const
    {
        return _specular_exponent;
    }

    material get_default_material()
    {
        // From the ES 1.1.12 spec, table 2.8, pg 39

        material mat;
        mat.ambient() = color(0.2f, 0.2f, 0.2f, 1.0f);
        mat.diffuse() = color(0.8f, 0.8f, 0.8f, 1.0f);
        mat.specular() = color(0.0f, 0.0f, 0.0f, 1.0f);
        mat.emissive() = color(0.0f, 0.0f, 0.0f, 1.0f);
        mat.specular_exponent() = 0.0f;
        return mat;
    }
}
