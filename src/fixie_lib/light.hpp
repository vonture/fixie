#ifndef _LIGHT_HPP_
#define _LIGHT_HPP_

#include "fixie_lib/color.hpp"
#include "fixie_lib/vector.hpp"

namespace fixie
{
    class light
    {
    public:
        light();

        GLboolean& enabled();
        const GLboolean& enabled() const;

        color& ambient();
        const color& ambient() const;

        color& diffuse();
        const color& diffuse() const;

        color& specular();
        const color& specular() const;

        vector4& position();
        const vector4& position() const;

        vector3& spot_direction();
        const vector3& spot_direction() const;

        GLfloat& spot_exponent();
        const GLfloat& spot_exponent() const;

        GLfloat& spot_cutoff();
        const GLfloat& spot_cutoff() const;

        GLfloat& constant_attenuation();
        const GLfloat& constant_attenuation() const;

        GLfloat& linear_attenuation();
        const GLfloat& linear_attenuation() const;

        GLfloat& quadratic_attenuation();
        const GLfloat& quadratic_attenuation() const;

    private:
        GLboolean _enabled;
        color _ambient;
        color _diffuse;
        color _specular;
        vector4 _position;
        vector3 _spot_direction;
        GLfloat _spot_exponent;
        GLfloat _spot_cutoff;
        GLfloat _constant_attenuation;
        GLfloat _linear_attenuation;
        GLfloat _quadratic_attenuation;
    };

    light get_default_light(size_t idx);
}

#endif // _LIGHT_HPP_
