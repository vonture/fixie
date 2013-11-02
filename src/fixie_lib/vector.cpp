#include "fixie_lib/vector.hpp"

#include <math.h>

namespace fixie
{
    vector3::vector3()
    {
        _data[0] = 0.0f;
        _data[1] = 0.0f;
        _data[2] = 0.0f;
    }

    vector3::vector3(GLfloat x, GLfloat y, GLfloat z)
    {
        _data[0] = x;
        _data[1] = y;
        _data[2] = z;
    }

    vector3::vector3(const GLfloat data[3])
    {
        _data[0] = data[0];
        _data[1] = data[1];
        _data[2] = data[2];
    }

    const GLfloat& vector3::x() const
    {
        return _data[0];
    }

    GLfloat& vector3::x()
    {
        return _data[0];
    }

    const GLfloat& vector3::y() const
    {
        return _data[1];
    }

    GLfloat& vector3::y()
    {
        return _data[1];
    }

    const GLfloat& vector3::z() const
    {
        return _data[2];
    }

    GLfloat& vector3::z()
    {
        return _data[2];
    }

    const GLfloat* vector3::data() const
    {
        return _data.data();
    }

    const GLfloat& vector3::operator()(size_t idx) const
    {
        return _data[idx];
    }

    GLfloat& vector3::operator()(size_t idx)
    {
        return _data[idx];
    }

    GLfloat vector3::length(const vector3& vec)
    {
        GLfloat len_squared = length_squared(vec);
        return (len_squared != 0.0f) ? sqrt(len_squared) : 0.0f;
    }

    GLfloat vector3::length_squared(const vector3& vec)
    {
        return vec._data[0] * vec._data[0] +
               vec._data[1] * vec._data[1] +
               vec._data[2] * vec._data[2];
    }

    vector3 vector3::normalize(const vector3& vec)
    {
        vector3 ret(0.0f, 0.0f, 0.0f);
        GLfloat len = length(vec);
        if (len != 0.0f)
        {
            GLfloat inv_len = 1.0f / len;
            ret.x() = vec.x() * inv_len;
            ret.y() = vec.y() * inv_len;
            ret.z() = vec.z() * inv_len;
        }
        return ret;
    }

    GLfloat vector3::dot(const vector3& a, const vector3& b)
    {
        return a._data[0] * b._data[0] +
               a._data[1] * b._data[1] +
               a._data[2] * b._data[2];
    }

    vector3 vector3::cross(const vector3& a, const vector3& b)
    {
        return vector3(a._data[1] * b._data[2],
                       a._data[2] * b._data[0],
                       a._data[0] * b._data[1]);
    }

    vector4::vector4()
    {
        _data[0] = 0.0f;
        _data[1] = 0.0f;
        _data[2] = 0.0f;
        _data[3] = 0.0f;
    }

    vector4::vector4(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
    {
        _data[0] = x;
        _data[1] = y;
        _data[2] = z;
        _data[3] = w;
    }

    vector4::vector4(const GLfloat data[4])
    {
        _data[0] = data[0];
        _data[1] = data[1];
        _data[2] = data[2];
        _data[3] = data[3];
    }

    const GLfloat& vector4::x() const
    {
        return _data[0];
    }

    GLfloat& vector4::x()
    {
        return _data[0];
    }

    const GLfloat& vector4::y() const
    {
        return _data[1];
    }

    GLfloat& vector4::y()
    {
        return _data[1];
    }

    const GLfloat& vector4::z() const
    {
        return _data[2];
    }

    GLfloat& vector4::z()
    {
        return _data[2];
    }

    const GLfloat& vector4::w() const
    {
        return _data[3];
    }

    GLfloat& vector4::w()
    {
        return _data[3];
    }

    const GLfloat* vector4::data() const
    {
        return _data.data();
    }

    const GLfloat& vector4::operator()(size_t idx) const
    {
        return _data[idx];
    }

    GLfloat& vector4::operator()(size_t idx)
    {
        return _data[idx];
    }

    GLfloat vector4::length(const vector4& vec)
    {
        GLfloat len_squared = length_squared(vec);
        return (len_squared != 0.0f) ? sqrt(len_squared) : 0.0f;
    }

    GLfloat vector4::length_squared(const vector4& vec)
    {
        return vec._data[0] * vec._data[0] +
               vec._data[1] * vec._data[1] +
               vec._data[2] * vec._data[2] +
               vec._data[3] * vec._data[3];
    }

    vector4 vector4::normalize(const vector4& vec)
    {
        vector4 ret(0.0f, 0.0f, 0.0f, 1.0f);
        if (vec.w() != 0.0f)
        {
            GLfloat inv_len = 1.0f / vec.w();
            ret.x() = vec.x() * inv_len;
            ret.y() = vec.y() * inv_len;
            ret.z() = vec.z() * inv_len;
        }
        return ret;
    }

    GLfloat vector4::dot(const vector4& a, const vector4& b)
    {
        return a._data[0] * b._data[0] +
               a._data[1] * b._data[1] +
               a._data[2] * b._data[2] +
               a._data[3] * b._data[3];
    }
}
