#include "fixie_lib/vector.hpp"

#include <math.h>

namespace fixie
{
    vector3::vector3()
        : x(0.0f)
        , y(0.0f)
        , z(0.0f)
    {
    }

    vector3::vector3(GLfloat x, GLfloat y, GLfloat z)
        : x(x)
        , y(y)
        , z(z)
    {
    }

    vector3::vector3(const GLfloat data[3])
        : x(data[0])
        , y(data[1])
        , z(data[2])
    {
    }

    const GLfloat& vector3::operator()(size_t idx) const
    {
        return data[idx];
    }

    GLfloat& vector3::operator()(size_t idx)
    {
        return data[idx];
    }

    GLfloat vector3::length(const vector3& vec)
    {
        GLfloat len_squared = length_squared(vec);
        return (len_squared != 0.0f) ? sqrt(len_squared) : 0.0f;
    }

    GLfloat vector3::length_squared(const vector3& vec)
    {
        return vec.data[0] * vec.data[0] +
               vec.data[1] * vec.data[1] +
               vec.data[2] * vec.data[2];
    }

    vector3 vector3::normalize(const vector3& vec)
    {
        vector3 ret(0.0f, 0.0f, 0.0f);
        GLfloat len = length(vec);
        if (len != 0.0f)
        {
            GLfloat inv_len = 1.0f / len;
            ret.x = vec.x * inv_len;
            ret.y = vec.y * inv_len;
            ret.z = vec.z * inv_len;
        }
        return ret;
    }

    GLfloat vector3::dot(const vector3& a, const vector3& b)
    {
        return a.data[0] * b.data[0] +
               a.data[1] * b.data[1] +
               a.data[2] * b.data[2];
    }

    vector3 vector3::cross(const vector3& a, const vector3& b)
    {
        return vector3(a.data[1] * b.data[2],
                       a.data[2] * b.data[0],
                       a.data[0] * b.data[1]);
    }

    vector4::vector4()
        : x(0.0f)
        , y(0.0f)
        , z(0.0f)
        , w(1.0f)
    {
    }

    vector4::vector4(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
        : x(x)
        , y(y)
        , z(z)
        , w(w)
    {
    }

    vector4::vector4(const GLfloat data[4])
        : x(data[0])
        , y(data[1])
        , z(data[2])
        , w(data[3])
    {
    }

    const GLfloat& vector4::operator()(size_t idx) const
    {
        return data[idx];
    }

    GLfloat& vector4::operator()(size_t idx)
    {
        return data[idx];
    }

    GLfloat vector4::length(const vector4& vec)
    {
        GLfloat len_squared = length_squared(vec);
        return (len_squared != 0.0f) ? sqrt(len_squared) : 0.0f;
    }

    GLfloat vector4::length_squared(const vector4& vec)
    {
        return vec.data[0] * vec.data[0] +
               vec.data[1] * vec.data[1] +
               vec.data[2] * vec.data[2] +
               vec.data[3] * vec.data[3];
    }

    vector4 vector4::normalize(const vector4& vec)
    {
        vector4 ret(0.0f, 0.0f, 0.0f, 1.0f);
        if (vec.w != 0.0f)
        {
            GLfloat inv_len = 1.0f / vec.w;
            ret.x = vec.x * inv_len;
            ret.y = vec.y * inv_len;
            ret.z = vec.z * inv_len;
        }
        return ret;
    }

    GLfloat vector4::dot(const vector4& a, const vector4& b)
    {
        return a.data[0] * b.data[0] +
               a.data[1] * b.data[1] +
               a.data[2] * b.data[2] +
               a.data[3] * b.data[3];
    }
}
