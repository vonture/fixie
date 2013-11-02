#include "fixie_lib/matrix.hpp"

#include <math.h>

namespace fixie
{
    matrix4::matrix4()
    {
        _data[ 0] = 1.0f; _data[ 4] = 0.0f; _data[ 8] = 0.0f; _data[12] = 0.0f;
        _data[ 1] = 0.0f; _data[ 5] = 1.0f; _data[ 9] = 0.0f; _data[13] = 0.0f;
        _data[ 2] = 0.0f; _data[ 6] = 0.0f; _data[10] = 1.0f; _data[14] = 0.0f;
        _data[ 3] = 0.0f; _data[ 7] = 0.0f; _data[11] = 0.0f; _data[15] = 1.0f;
    }

    matrix4::matrix4(GLfloat m00, GLfloat m01, GLfloat m02, GLfloat m03,
                     GLfloat m10, GLfloat m11, GLfloat m12, GLfloat m13,
                     GLfloat m20, GLfloat m21, GLfloat m22, GLfloat m23,
                     GLfloat m30, GLfloat m31, GLfloat m32, GLfloat m33)
    {
        _data[ 0] = m00; _data[ 4] = m01; _data[ 8] = m02; _data[12] = m03;
        _data[ 1] = m10; _data[ 5] = m11; _data[ 9] = m12; _data[13] = m13;
        _data[ 2] = m20; _data[ 6] = m21; _data[10] = m22; _data[14] = m23;
        _data[ 3] = m30; _data[ 7] = m31; _data[11] = m32; _data[15] = m33;
    }

    matrix4::matrix4(const GLfloat arr[16])
    {
        _data[ 0] = arr[ 0]; _data[ 4] = arr[ 4]; _data[ 8] = arr[ 8]; _data[12] = arr[12];
        _data[ 1] = arr[ 1]; _data[ 5] = arr[ 5]; _data[ 9] = arr[ 9]; _data[13] = arr[13];
        _data[ 2] = arr[ 2]; _data[ 6] = arr[ 6]; _data[10] = arr[10]; _data[14] = arr[14];
        _data[ 3] = arr[ 3]; _data[ 7] = arr[ 7]; _data[11] = arr[11]; _data[15] = arr[15];
    }

    const GLfloat* matrix4::data() const
    {
        return _data.data();
    }

    const GLfloat& matrix4::operator()(size_t row, size_t col) const
    {
        return _data[col * 4 + row];
    }

    GLfloat& matrix4::operator()(size_t row, size_t col)
    {
        return _data[col * 4 + row];
    }

    matrix4 matrix4::identity()
    {
        return matrix4(1.0f, 0.0f, 0.0f, 0.0f,
                       0.0f, 1.0f, 0.0f, 0.0f,
                       0.0f, 0.0f, 1.0f, 0.0f,
                       0.0f, 0.0f, 0.0f, 1.0f);
    }

    matrix4 matrix4::rotate(GLfloat angle, const vector3& p)
    {
        vector3 u = vector3::normalize(p);
        GLfloat theta = angle * 0.0174532925f;
        GLfloat cos_t = cosf(theta);
        GLfloat sin_t = sinf(theta);

        return matrix4(          cos_t + (u.x() * u.x() * (1.0f - cos_t)), (u.x() * u.y() * (1.0f - cos_t)) - (u.z() * sin_t), (u.x() * u.z() * (1.0f - cos_t)) + (u.y() * sin_t), 0.0f,
                       (u.y() * u.x() * (1.0f - cos_t)) + (u.z() * sin_t),           cos_t + (u.y() * u.y() * (1.0f - cos_t)), (u.y() * u.z() * (1.0f - cos_t)) - (u.x() * sin_t), 0.0f,
                       (u.z() * u.x() * (1.0f - cos_t)) - (u.y() * sin_t), (u.z() * u.y() * (1.0f - cos_t)) + (u.x() * sin_t),           cos_t + (u.z() * u.z() * (1.0f - cos_t)), 0.0f,
                                                                     0.0f,                                               0.0f,                                               0.0f, 1.0f);
    }

    matrix4 matrix4::translate(const vector3& t)
    {
        return matrix4(1.0f, 0.0f, 0.0f, t.x(),
                       0.0f, 1.0f, 0.0f, t.y(),
                       0.0f, 0.0f, 1.0f, t.z(),
                       0.0f, 0.0f, 0.0f,  1.0f);
    }

    matrix4 matrix4::scale(const vector3& s)
    {
        return matrix4(s.x(),  0.0f,  0.0f, 0.0f,
                        0.0f, s.y(),  0.0f, 0.0f,
                        0.0f,  0.0f, s.z(), 0.0f,
                        0.0f,  0.0f,  0.0f, 1.0f);
    }

    matrix4 matrix4::frustum(GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f)
    {
        return matrix4((2.0f * n) / (r - l),                 0.0f,  (r + l) / (r - l),                      0.0f,
                                       0.0f, (2.0f * n) / (t - b),  (t + b) / (t - b),                      0.0f,
                                       0.0f,                 0.0f, -(f + n) / (f - n), -(2.0f * f * n) / (f - n),
                                       0.0f,                 0.0f,              -1.0f,                      0.0f);
    }

    matrix4 matrix4::ortho(GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f)
    {
        return matrix4(2.0f / (r - l),           0.0f,            0.0f, -(r + l) / (r - l),
                                 0.0f, 2.0f / (t - b),            0.0f, -(t + b) / (t - b),
                                 0.0f,           0.0f, -2.0f / (f - n), -(f + n) / (f - n),
                                 0.0f,           0.0f,            0.0f,               1.0f);
    }

    matrix4 matrix4::invert(const matrix4& mat)
    {
        matrix4 inverted( mat._data[ 5] * mat._data[10] * mat._data[15] - mat._data[5] * mat._data[11] * mat._data[14] - mat._data[ 9] * mat._data[ 6] * mat._data[15] + mat._data[ 9] * mat._data[ 7] * mat._data[14] + mat._data[13] * mat._data[ 6] * mat._data[11] - mat._data[13] * mat._data[ 7] * mat._data[10],
                         -mat._data[ 4] * mat._data[10] * mat._data[15] + mat._data[4] * mat._data[11] * mat._data[14] + mat._data[ 8] * mat._data[ 6] * mat._data[15] - mat._data[ 8] * mat._data[ 7] * mat._data[14] - mat._data[12] * mat._data[ 6] * mat._data[11] + mat._data[12] * mat._data[ 7] * mat._data[10],
                          mat._data[ 4] * mat._data[ 9] * mat._data[15] - mat._data[4] * mat._data[11] * mat._data[13] - mat._data[ 8] * mat._data[ 5] * mat._data[15] + mat._data[ 8] * mat._data[ 7] * mat._data[13] + mat._data[12] * mat._data[ 5] * mat._data[11] - mat._data[12] * mat._data[ 7] * mat._data[ 9],
                         -mat._data[ 4] * mat._data[ 9] * mat._data[14] + mat._data[4] * mat._data[10] * mat._data[13] + mat._data[ 8] * mat._data[ 5] * mat._data[14] - mat._data[ 8] * mat._data[ 6] * mat._data[13] - mat._data[12] * mat._data[ 5] * mat._data[10] + mat._data[12] * mat._data[ 6] * mat._data[ 9],
                         -mat._data[ 1] * mat._data[10] * mat._data[15] + mat._data[1] * mat._data[11] * mat._data[14] + mat._data[ 9] * mat._data[ 2] * mat._data[15] - mat._data[ 9] * mat._data[ 3] * mat._data[14] - mat._data[13] * mat._data[ 2] * mat._data[11] + mat._data[13] * mat._data[ 3] * mat._data[10],
                          mat._data[ 0] * mat._data[10] * mat._data[15] - mat._data[0] * mat._data[11] * mat._data[14] - mat._data[ 8] * mat._data[ 2] * mat._data[15] + mat._data[ 8] * mat._data[ 3] * mat._data[14] + mat._data[12] * mat._data[ 2] * mat._data[11] - mat._data[12] * mat._data[ 3] * mat._data[10],
                         -mat._data[ 0] * mat._data[ 9] * mat._data[15] + mat._data[0] * mat._data[11] * mat._data[13] + mat._data[ 8] * mat._data[ 1] * mat._data[15] - mat._data[ 8] * mat._data[ 3] * mat._data[13] - mat._data[12] * mat._data[ 1] * mat._data[11] + mat._data[12] * mat._data[ 3] * mat._data[ 9],
                          mat._data[ 0] * mat._data[ 9] * mat._data[14] - mat._data[0] * mat._data[10] * mat._data[13] - mat._data[ 8] * mat._data[ 1] * mat._data[14] + mat._data[ 8] * mat._data[ 2] * mat._data[13] + mat._data[12] * mat._data[ 1] * mat._data[10] - mat._data[12] * mat._data[ 2] * mat._data[ 9],
                          mat._data[ 1] * mat._data[ 6] * mat._data[15] - mat._data[1] * mat._data[ 7] * mat._data[14] - mat._data[ 5] * mat._data[ 2] * mat._data[15] + mat._data[ 5] * mat._data[ 3] * mat._data[14] + mat._data[13] * mat._data[ 2] * mat._data[ 7] - mat._data[13] * mat._data[ 3] * mat._data[ 6],
                         -mat._data[ 0] * mat._data[ 6] * mat._data[15] + mat._data[0] * mat._data[ 7] * mat._data[14] + mat._data[ 4] * mat._data[ 2] * mat._data[15] - mat._data[ 4] * mat._data[ 3] * mat._data[14] - mat._data[12] * mat._data[ 2] * mat._data[ 7] + mat._data[12] * mat._data[ 3] * mat._data[ 6],
                          mat._data[ 0] * mat._data[ 5] * mat._data[15] - mat._data[0] * mat._data[ 7] * mat._data[13] - mat._data[ 4] * mat._data[ 1] * mat._data[15] + mat._data[ 4] * mat._data[ 3] * mat._data[13] + mat._data[12] * mat._data[ 1] * mat._data[ 7] - mat._data[12] * mat._data[ 3] * mat._data[ 5],
                         -mat._data[ 0] * mat._data[ 5] * mat._data[14] + mat._data[0] * mat._data[ 6] * mat._data[13] + mat._data[ 4] * mat._data[ 1] * mat._data[14] - mat._data[ 4] * mat._data[ 2] * mat._data[13] - mat._data[12] * mat._data[ 1] * mat._data[ 6] + mat._data[12] * mat._data[ 2] * mat._data[ 5],
                         -mat._data[ 1] * mat._data[ 6] * mat._data[11] + mat._data[1] * mat._data[ 7] * mat._data[10] + mat._data[ 5] * mat._data[ 2] * mat._data[11] - mat._data[ 5] * mat._data[ 3] * mat._data[10] - mat._data[ 9] * mat._data[ 2] * mat._data[ 7] + mat._data[ 9] * mat._data[ 3] * mat._data[ 6],
                          mat._data[ 0] * mat._data[ 6] * mat._data[11] - mat._data[0] * mat._data[ 7] * mat._data[10] - mat._data[ 4] * mat._data[ 2] * mat._data[11] + mat._data[ 4] * mat._data[ 3] * mat._data[10] + mat._data[ 8] * mat._data[ 2] * mat._data[ 7] - mat._data[ 8] * mat._data[ 3] * mat._data[ 6],
                         -mat._data[ 0] * mat._data[ 5] * mat._data[11] + mat._data[0] * mat._data[ 7] * mat._data[ 9] + mat._data[ 4] * mat._data[ 1] * mat._data[11] - mat._data[ 4] * mat._data[ 3] * mat._data[ 9] - mat._data[ 8] * mat._data[ 1] * mat._data[ 7] + mat._data[ 8] * mat._data[ 3] * mat._data[ 5],
                          mat._data[ 0] * mat._data[ 5] * mat._data[10] - mat._data[0] * mat._data[ 6] * mat._data[ 9] - mat._data[ 4] * mat._data[ 1] * mat._data[10] + mat._data[ 4] * mat._data[ 2] * mat._data[ 9] + mat._data[ 8] * mat._data[ 1] * mat._data[ 6] - mat._data[ 8] * mat._data[ 2] * mat._data[ 5]);

        GLfloat determinant = mat._data[0] * inverted._data[0] + mat._data[1] * inverted._data[4] + mat._data[2] * inverted._data[8] + mat._data[3] * inverted._data[12];

        if (determinant != 0.0f)
        {
            inverted *= 1.0f / determinant;
        }
        else
        {
            inverted = identity();
        }

        return inverted;
    }

    matrix4 matrix4::transpose(const matrix4& mat)
    {
        return matrix4(mat._data[ 0], mat._data[ 1], mat._data[ 2], mat._data[ 3],
                       mat._data[ 4], mat._data[ 5], mat._data[ 6], mat._data[ 7],
                       mat._data[ 8], mat._data[ 9], mat._data[10], mat._data[11],
                       mat._data[12], mat._data[13], mat._data[14], mat._data[15]);
    }

    vector3 matrix4::transform(const matrix4& mat, const vector3& pt)
    {
        vector4 transformed = mat * vector4(pt.x(), pt.y(), pt.z(), 1.0f);
        vector4::normalize(transformed);
        return vector3(transformed.x(), transformed.y(), transformed.z());
    }

    matrix4 operator*(const matrix4& a, const matrix4& b)
    {
        return matrix4(b(0, 0) * a(0, 0) + b(0, 1) * a(1, 0) + b(0, 2) * a(2, 0) + b(0, 3) * a(3, 0),
                       b(0, 0) * a(0, 1) + b(0, 1) * a(1, 1) + b(0, 2) * a(2, 1) + b(0, 3) * a(3, 1),
                       b(0, 0) * a(0, 2) + b(0, 1) * a(1, 2) + b(0, 2) * a(2, 2) + b(0, 3) * a(3, 2),
                       b(0, 0) * a(0, 3) + b(0, 1) * a(1, 3) + b(0, 2) * a(2, 3) + b(0, 3) * a(3, 3),
                       b(1, 0) * a(0, 0) + b(1, 1) * a(1, 0) + b(1, 2) * a(2, 0) + b(1, 3) * a(3, 0),
                       b(1, 0) * a(0, 1) + b(1, 1) * a(1, 1) + b(1, 2) * a(2, 1) + b(1, 3) * a(3, 1),
                       b(1, 0) * a(0, 2) + b(1, 1) * a(1, 2) + b(1, 2) * a(2, 2) + b(1, 3) * a(3, 2),
                       b(1, 0) * a(0, 3) + b(1, 1) * a(1, 3) + b(1, 2) * a(2, 3) + b(1, 3) * a(3, 3),
                       b(2, 0) * a(0, 0) + b(2, 1) * a(1, 0) + b(2, 2) * a(2, 0) + b(2, 3) * a(3, 0),
                       b(2, 0) * a(0, 1) + b(2, 1) * a(1, 1) + b(2, 2) * a(2, 1) + b(2, 3) * a(3, 1),
                       b(2, 0) * a(0, 2) + b(2, 1) * a(1, 2) + b(2, 2) * a(2, 2) + b(2, 3) * a(3, 2),
                       b(2, 0) * a(0, 3) + b(2, 1) * a(1, 3) + b(2, 2) * a(2, 3) + b(2, 3) * a(3, 3),
                       b(3, 0) * a(0, 0) + b(3, 1) * a(1, 0) + b(3, 2) * a(2, 0) + b(3, 3) * a(3, 0),
                       b(3, 0) * a(0, 1) + b(3, 1) * a(1, 1) + b(3, 2) * a(2, 1) + b(3, 3) * a(3, 1),
                       b(3, 0) * a(0, 2) + b(3, 1) * a(1, 2) + b(3, 2) * a(2, 2) + b(3, 3) * a(3, 2),
                       b(3, 0) * a(0, 3) + b(3, 1) * a(1, 3) + b(3, 2) * a(2, 3) + b(3, 3) * a(3, 3));
    }

    matrix4& operator*=(matrix4& a, const matrix4& b)
    {
        a = a * b;
        return a;
    }

    matrix4 operator*(const matrix4& a, GLfloat b)
    {
        matrix4 ret(a);
        for (size_t i = 0; i < 4; ++i)
        {
            for (size_t j = 0; j < 4; ++j)
            {
                ret(i, j) *= b;
            }
        }
        return ret;
    }

    matrix4& operator*=(matrix4& a, GLfloat b)
    {
        for (size_t i = 0; i < 4; ++i)
        {
            for (size_t j = 0; j < 4; ++j)
            {
                a(i, j) *= b;
            }
        }
        return a;
    }

    vector4 operator*(const matrix4& a, const vector4& b)
    {
        return vector4(a(0, 0) * b.x() + a(0, 1) * b.y() + a(0, 2) * b.z() + a(0, 3) * b.w(),
                       a(1, 0) * b.x() + a(1, 1) * b.y() + a(1, 2) * b.z() + a(1, 3) * b.w(),
                       a(2, 0) * b.x() + a(2, 1) * b.y() + a(2, 2) * b.z() + a(2, 3) * b.w(),
                       a(3, 0) * b.x() + a(3, 1) * b.y() + a(3, 2) * b.z() + a(3, 3) * b.w());
    }

    bool operator==(const matrix4& a, const matrix4& b)
    {
        return a(0, 0) == b(0, 0) && a(0, 1) == b(0, 1) && a(0, 2) == b(0, 2) && a(0, 3) == b(0, 3) &&
               a(1, 0) == b(1, 0) && a(1, 1) == b(1, 1) && a(1, 2) == b(1, 2) && a(1, 3) == b(1, 3) &&
               a(2, 0) == b(2, 0) && a(2, 1) == b(2, 1) && a(2, 2) == b(2, 2) && a(2, 3) == b(2, 3) &&
               a(3, 0) == b(3, 0) && a(3, 1) == b(3, 1) && a(3, 2) == b(3, 3) && a(3, 3) == b(3, 3);
    }

    bool operator!=(const matrix4& a, const matrix4& b)
    {
        return !(a == b);
    }
}
