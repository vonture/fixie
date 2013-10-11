#include "fixie_lib/light.hpp"
#include "fixie/fixie_gl_es.h"

namespace fixie
{
    light::light()
        : _enabled(GL_FALSE)
        , _ambient()
        , _diffuse()
        , _specular()
        , _position()
        , _spot_direction()
        , _spot_exponent(0.0f)
        , _spot_cutoff(0.0f)
        , _constant_attenuation(0.0f)
        , _quadratic_attenuation(0.0f)
    {
    }

    GLboolean& light::enabled()
    {
        return _enabled;
    }

    const GLboolean& light::enabled() const
    {
        return _enabled;
    }

    color& light::ambient()
    {
        return _ambient;
    }

    const color& light::ambient() const
    {
        return _ambient;
    }

    color& light::diffuse()
    {
        return _diffuse;
    }

    const color& light::diffuse() const
    {
        return _diffuse;
    }

    color& light::specular()
    {
        return _specular;
    }

    const color& light::specular() const
    {
        return _specular;
    }

    vector4& light::position()
    {
        return _position;
    }

    const vector4& light::position() const
    {
        return _position;
    }

    vector3& light::spot_direction()
    {
        return _spot_direction;
    }

    const vector3& light::spot_direction() const
    {
        return _spot_direction;
    }

    GLfloat& light::spot_exponent()
    {
        return _spot_exponent;
    }

    const GLfloat& light::spot_exponent() const
    {
        return _spot_exponent;
    }

    GLfloat& light::spot_cutoff()
    {
        return _spot_cutoff;
    }

    const GLfloat& light::spot_cutoff() const
    {
        return _spot_cutoff;
    }

    GLfloat& light::constant_attenuation()
    {
        return _constant_attenuation;
    }

    const GLfloat& light::constant_attenuation() const
    {
        return _constant_attenuation;
    }

    GLfloat& light::linear_attenuation()
    {
        return _linear_attenuation;
    }

    const GLfloat& light::linear_attenuation() const
    {
        return _linear_attenuation;
    }

    GLfloat& light::quadratic_attenuation()
    {
        return _quadratic_attenuation;
    }

    const GLfloat& light::quadratic_attenuation() const
    {
        return _quadratic_attenuation;
    }

    light get_default_light(size_t idx)
    {
        // From the ES 1.1.12 spec, table 2.8, pg 39

        light light;
        light.enabled() = GL_FALSE;
        light.ambient() = color(0.0f, 0.0f, 0.0f, 1.0f);
        light.diffuse() = (idx > 0) ? color(0.0f, 0.0f, 0.0f, 1.0f) : color(1.0f, 1.0f, 1.0f, 1.0f);
        light.specular() = (idx > 0) ? color(0.0f, 0.0f, 0.0f, 1.0f) : color(1.0f, 1.0f, 1.0f, 1.0f);
        light.position() = vector4(0.0f, 0.0f, 1.0f, 0.0f);
        light.spot_direction() = vector3(0.0f, 0.0f, -1.0f);
        light.spot_exponent() = 0.0f;
        light.spot_cutoff() = 180.0f;
        light.constant_attenuation() = 1.0f;
        light.linear_attenuation() = 0.0f;
        light.quadratic_attenuation() = 0.0f;
        return light;
    }
}
