#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

#include "fixie_gl_types.h"

namespace fixie
{
    struct vector3
    {
        union
        {
            struct
            {
                GLfloat x, y, z;
            };
            GLfloat data[3];
        };

        vector3();
        vector3(GLfloat x, GLfloat y, GLfloat z);
        vector3(const GLfloat data[3]);

        const GLfloat& operator()(size_t idx) const;
        GLfloat& operator()(size_t idx);

        static GLfloat length(const vector3& vec);
        static GLfloat length_squared(const vector3& vec);

        static vector3 normalize(const vector3& vec);

        static GLfloat dot(const vector3& a, const vector3& b);
        static vector3 cross(const vector3& a, const vector3& b);
    };

    struct vector4
    {
        union
        {
            struct
            {
                GLfloat x, y, z, w;
            };
            GLfloat data[4];
        };

        vector4();
        vector4(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
        vector4(const GLfloat data[4]);

        const GLfloat& operator()(size_t idx) const;
        GLfloat& operator()(size_t idx);

        static GLfloat length(const vector4& vec);
        static GLfloat length_squared(const vector4& vec);

        static vector4 normalize(const vector4& vec);

        static GLfloat dot(const vector4& a, const vector4& b);
    };
}

#endif // _VECTOR_HPP_
