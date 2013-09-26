#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

#include "fixie_gl_types.h"

namespace fixie
{
    struct vector3
    {
        GLfloat x, y, z;

        vector3();
        vector3(GLfloat X, GLfloat Y, GLfloat Z);
        vector3(const GLfloat data[3]);
    };

    struct vector4
    {
        GLfloat x, y, z, w;

        vector4();
        vector4(GLfloat X, GLfloat Y, GLfloat Z, GLfloat W);
        vector4(const GLfloat data[4]);
    };
}

#endif // _VECTOR_HPP_
