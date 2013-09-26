#ifndef _MATERIAL_HPP_
#define _MATERIAL_HPP_

#include "fixie_gl_types.h"
#include "color.hpp"

namespace fixie
{
    class material
    {
    public:
        material();

        color& ambient();
        const color& ambient() const;

        color& diffuse();
        const color& diffuse() const;

        color& specular();
        const color& specular() const;

        color& emissive();
        const color& emissive() const;

        GLfloat& specular_exponent();
        const GLfloat& specular_exponent() const;

    private:
        color _ambient;
        color _diffuse;
        color _specular;
        color _emissive;
        GLfloat _specular_exponent;
    };

    material get_default_material();
}

#endif // _MATERIAL_HPP_
