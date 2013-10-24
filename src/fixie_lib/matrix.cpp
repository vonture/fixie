#include "fixie_lib/matrix.hpp"

#include <math.h>

namespace fixie
{
    matrix4::matrix4()
    {
        data[ 0] = 1.0f; data[ 4] = 0.0f; data[ 8] = 0.0f; data[12] = 0.0f;
        data[ 1] = 0.0f; data[ 5] = 1.0f; data[ 9] = 0.0f; data[13] = 0.0f;
        data[ 2] = 0.0f; data[ 6] = 0.0f; data[10] = 1.0f; data[14] = 0.0f;
        data[ 3] = 0.0f; data[ 7] = 0.0f; data[11] = 0.0f; data[15] = 1.0f;
    }

    matrix4::matrix4(GLfloat m00, GLfloat m01, GLfloat m02, GLfloat m03,
                     GLfloat m10, GLfloat m11, GLfloat m12, GLfloat m13,
                     GLfloat m20, GLfloat m21, GLfloat m22, GLfloat m23,
                     GLfloat m30, GLfloat m31, GLfloat m32, GLfloat m33)
    {
        data[ 0] = m00; data[ 4] = m01; data[ 8] = m02; data[12] = m03;
        data[ 1] = m10; data[ 5] = m11; data[ 9] = m12; data[13] = m13;
        data[ 2] = m20; data[ 6] = m21; data[10] = m22; data[14] = m23;
        data[ 3] = m30; data[ 7] = m31; data[11] = m32; data[15] = m33;
    }

    matrix4::matrix4(const GLfloat arr[16])
    {
        data[ 0] = arr[ 0]; data[ 4] = arr[ 4]; data[ 8] = arr[ 8]; data[12] = arr[12];
        data[ 1] = arr[ 1]; data[ 5] = arr[ 5]; data[ 9] = arr[ 9]; data[13] = arr[13];
        data[ 2] = arr[ 2]; data[ 6] = arr[ 6]; data[10] = arr[10]; data[14] = arr[14];
        data[ 3] = arr[ 3]; data[ 7] = arr[ 7]; data[11] = arr[11]; data[15] = arr[15];
    }

    const vector4& matrix4::operator()(size_t col) const
    {
        return columns[col];
    }

    vector4& matrix4::operator()(size_t col)
    {
        return columns[col];
    }

    const GLfloat& matrix4::operator()(size_t row, size_t col) const
    {
        return data[col * 4 + row];
    }

    GLfloat& matrix4::operator()(size_t row, size_t col)
    {
        return data[col * 4 + row];
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

        return matrix4(        cos_t + (u.x * u.x * (1.0f - cos_t)), (u.x * u.y * (1.0f - cos_t)) - (u.z * sin_t), (u.x * u.z * (1.0f - cos_t)) + (u.y * sin_t), 0.0f,
                       (u.y * u.x * (1.0f - cos_t)) + (u.z * sin_t),         cos_t + (u.y * u.y * (1.0f - cos_t)), (u.y * u.z * (1.0f - cos_t)) - (u.x * sin_t), 0.0f,
                       (u.z * u.x * (1.0f - cos_t)) - (u.y * sin_t), (u.z * u.y * (1.0f - cos_t)) + (u.x * sin_t),         cos_t + (u.z * u.z * (1.0f - cos_t)), 0.0f,
                                                               0.0f,                                         0.0f,                                         0.0f, 1.0f);
    }

    matrix4 matrix4::translate(const vector3& t)
    {
        return matrix4(1.0f, 0.0f, 0.0f, t.x,
                       0.0f, 1.0f, 0.0f, t.y,
                       0.0f, 0.0f, 1.0f, t.z,
                       0.0f, 0.0f, 0.0f, 1.0f);
    }

    matrix4 matrix4::scale(const vector3& s)
    {
        return matrix4( s.x, 0.0f, 0.0f, 0.0f,
                       0.0f,  s.y, 0.0f, 0.0f,
                       0.0f, 0.0f,  s.z, 0.0f,
                       0.0f, 0.0f, 0.0f, 1.0f);
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
        matrix4 inverted( mat.data[ 5] * mat.data[10] * mat.data[15] - mat.data[5] * mat.data[11] * mat.data[14] - mat.data[ 9] * mat.data[ 6] * mat.data[15] + mat.data[ 9] * mat.data[ 7] * mat.data[14] + mat.data[13] * mat.data[ 6] * mat.data[11] - mat.data[13] * mat.data[ 7] * mat.data[10],
                         -mat.data[ 4] * mat.data[10] * mat.data[15] + mat.data[4] * mat.data[11] * mat.data[14] + mat.data[ 8] * mat.data[ 6] * mat.data[15] - mat.data[ 8] * mat.data[ 7] * mat.data[14] - mat.data[12] * mat.data[ 6] * mat.data[11] + mat.data[12] * mat.data[ 7] * mat.data[10],
                          mat.data[ 4] * mat.data[ 9] * mat.data[15] - mat.data[4] * mat.data[11] * mat.data[13] - mat.data[ 8] * mat.data[ 5] * mat.data[15] + mat.data[ 8] * mat.data[ 7] * mat.data[13] + mat.data[12] * mat.data[ 5] * mat.data[11] - mat.data[12] * mat.data[ 7] * mat.data[ 9],
                         -mat.data[ 4] * mat.data[ 9] * mat.data[14] + mat.data[4] * mat.data[10] * mat.data[13] + mat.data[ 8] * mat.data[ 5] * mat.data[14] - mat.data[ 8] * mat.data[ 6] * mat.data[13] - mat.data[12] * mat.data[ 5] * mat.data[10] + mat.data[12] * mat.data[ 6] * mat.data[ 9],
                         -mat.data[ 1] * mat.data[10] * mat.data[15] + mat.data[1] * mat.data[11] * mat.data[14] + mat.data[ 9] * mat.data[ 2] * mat.data[15] - mat.data[ 9] * mat.data[ 3] * mat.data[14] - mat.data[13] * mat.data[ 2] * mat.data[11] + mat.data[13] * mat.data[ 3] * mat.data[10],
                          mat.data[ 0] * mat.data[10] * mat.data[15] - mat.data[0] * mat.data[11] * mat.data[14] - mat.data[ 8] * mat.data[ 2] * mat.data[15] + mat.data[ 8] * mat.data[ 3] * mat.data[14] + mat.data[12] * mat.data[ 2] * mat.data[11] - mat.data[12] * mat.data[ 3] * mat.data[10],
                         -mat.data[ 0] * mat.data[ 9] * mat.data[15] + mat.data[0] * mat.data[11] * mat.data[13] + mat.data[ 8] * mat.data[ 1] * mat.data[15] - mat.data[ 8] * mat.data[ 3] * mat.data[13] - mat.data[12] * mat.data[ 1] * mat.data[11] + mat.data[12] * mat.data[ 3] * mat.data[ 9],
                          mat.data[ 0] * mat.data[ 9] * mat.data[14] - mat.data[0] * mat.data[10] * mat.data[13] - mat.data[ 8] * mat.data[ 1] * mat.data[14] + mat.data[ 8] * mat.data[ 2] * mat.data[13] + mat.data[12] * mat.data[ 1] * mat.data[10] - mat.data[12] * mat.data[ 2] * mat.data[ 9],
                          mat.data[ 1] * mat.data[ 6] * mat.data[15] - mat.data[1] * mat.data[ 7] * mat.data[14] - mat.data[ 5] * mat.data[ 2] * mat.data[15] + mat.data[ 5] * mat.data[ 3] * mat.data[14] + mat.data[13] * mat.data[ 2] * mat.data[ 7] - mat.data[13] * mat.data[ 3] * mat.data[ 6],
                         -mat.data[ 0] * mat.data[ 6] * mat.data[15] + mat.data[0] * mat.data[ 7] * mat.data[14] + mat.data[ 4] * mat.data[ 2] * mat.data[15] - mat.data[ 4] * mat.data[ 3] * mat.data[14] - mat.data[12] * mat.data[ 2] * mat.data[ 7] + mat.data[12] * mat.data[ 3] * mat.data[ 6],
                          mat.data[ 0] * mat.data[ 5] * mat.data[15] - mat.data[0] * mat.data[ 7] * mat.data[13] - mat.data[ 4] * mat.data[ 1] * mat.data[15] + mat.data[ 4] * mat.data[ 3] * mat.data[13] + mat.data[12] * mat.data[ 1] * mat.data[ 7] - mat.data[12] * mat.data[ 3] * mat.data[ 5],
                         -mat.data[ 0] * mat.data[ 5] * mat.data[14] + mat.data[0] * mat.data[ 6] * mat.data[13] + mat.data[ 4] * mat.data[ 1] * mat.data[14] - mat.data[ 4] * mat.data[ 2] * mat.data[13] - mat.data[12] * mat.data[ 1] * mat.data[ 6] + mat.data[12] * mat.data[ 2] * mat.data[ 5],
                         -mat.data[ 1] * mat.data[ 6] * mat.data[11] + mat.data[1] * mat.data[ 7] * mat.data[10] + mat.data[ 5] * mat.data[ 2] * mat.data[11] - mat.data[ 5] * mat.data[ 3] * mat.data[10] - mat.data[ 9] * mat.data[ 2] * mat.data[ 7] + mat.data[ 9] * mat.data[ 3] * mat.data[ 6],
                          mat.data[ 0] * mat.data[ 6] * mat.data[11] - mat.data[0] * mat.data[ 7] * mat.data[10] - mat.data[ 4] * mat.data[ 2] * mat.data[11] + mat.data[ 4] * mat.data[ 3] * mat.data[10] + mat.data[ 8] * mat.data[ 2] * mat.data[ 7] - mat.data[ 8] * mat.data[ 3] * mat.data[ 6],
                         -mat.data[ 0] * mat.data[ 5] * mat.data[11] + mat.data[0] * mat.data[ 7] * mat.data[ 9] + mat.data[ 4] * mat.data[ 1] * mat.data[11] - mat.data[ 4] * mat.data[ 3] * mat.data[ 9] - mat.data[ 8] * mat.data[ 1] * mat.data[ 7] + mat.data[ 8] * mat.data[ 3] * mat.data[ 5],
                          mat.data[ 0] * mat.data[ 5] * mat.data[10] - mat.data[0] * mat.data[ 6] * mat.data[ 9] - mat.data[ 4] * mat.data[ 1] * mat.data[10] + mat.data[ 4] * mat.data[ 2] * mat.data[ 9] + mat.data[ 8] * mat.data[ 1] * mat.data[ 6] - mat.data[ 8] * mat.data[ 2] * mat.data[ 5]);

        GLfloat determinant = mat.data[0] * inverted.data[0] + mat.data[1] * inverted.data[4] + mat.data[2] * inverted.data[8] + mat.data[3] * inverted.data[12];

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
        return matrix4(mat.data[ 0], mat.data[ 1], mat.data[ 2], mat.data[ 3],
                       mat.data[ 4], mat.data[ 5], mat.data[ 6], mat.data[ 7],
                       mat.data[ 8], mat.data[ 9], mat.data[10], mat.data[11],
                       mat.data[12], mat.data[13], mat.data[14], mat.data[15]);
    }

    vector3 matrix4::transform(const matrix4& mat, const vector3& pt)
    {
        vector4 transformed = mat * vector4(pt.x, pt.y, pt.z, 1.0f);
        vector4::normalize(transformed);
        return vector3(transformed.x, transformed.y, transformed.z);
    }

    matrix4 operator*(const matrix4& a, const matrix4& b)
    {
        return matrix4(b.data[ 0] * a.data[ 0] + b.data[ 4] * a.data[ 1] + b.data[ 8] * a.data[ 2] + b.data[12] * a.data[ 3],
                       b.data[ 0] * a.data[ 4] + b.data[ 4] * a.data[ 5] + b.data[ 8] * a.data[ 6] + b.data[12] * a.data[ 7],
                       b.data[ 0] * a.data[ 8] + b.data[ 4] * a.data[ 9] + b.data[ 8] * a.data[10] + b.data[12] * a.data[11],
                       b.data[ 0] * a.data[12] + b.data[ 4] * a.data[13] + b.data[ 8] * a.data[14] + b.data[12] * a.data[15],
                       b.data[ 1] * a.data[ 0] + b.data[ 5] * a.data[ 1] + b.data[ 9] * a.data[ 2] + b.data[13] * a.data[ 3],
                       b.data[ 1] * a.data[ 4] + b.data[ 5] * a.data[ 5] + b.data[ 9] * a.data[ 6] + b.data[13] * a.data[ 7],
                       b.data[ 1] * a.data[ 8] + b.data[ 5] * a.data[ 9] + b.data[ 9] * a.data[10] + b.data[13] * a.data[11],
                       b.data[ 1] * a.data[12] + b.data[ 5] * a.data[13] + b.data[ 9] * a.data[14] + b.data[13] * a.data[15],
                       b.data[ 2] * a.data[ 0] + b.data[ 6] * a.data[ 1] + b.data[10] * a.data[ 2] + b.data[14] * a.data[ 3],
                       b.data[ 2] * a.data[ 4] + b.data[ 6] * a.data[ 5] + b.data[10] * a.data[ 6] + b.data[14] * a.data[ 7],
                       b.data[ 2] * a.data[ 8] + b.data[ 6] * a.data[ 9] + b.data[10] * a.data[10] + b.data[14] * a.data[11],
                       b.data[ 2] * a.data[12] + b.data[ 6] * a.data[13] + b.data[10] * a.data[14] + b.data[14] * a.data[15],
                       b.data[ 3] * a.data[ 0] + b.data[ 7] * a.data[ 1] + b.data[11] * a.data[ 2] + b.data[15] * a.data[ 3],
                       b.data[ 3] * a.data[ 4] + b.data[ 7] * a.data[ 5] + b.data[11] * a.data[ 6] + b.data[15] * a.data[ 7],
                       b.data[ 3] * a.data[ 8] + b.data[ 7] * a.data[ 9] + b.data[11] * a.data[10] + b.data[15] * a.data[11],
                       b.data[ 3] * a.data[12] + b.data[ 7] * a.data[13] + b.data[11] * a.data[14] + b.data[15] * a.data[15]);
    }

    matrix4& operator*=(matrix4& a, const matrix4& b)
    {
        a = a * b;
        return a;
    }

    matrix4 operator*(const matrix4& a, GLfloat b)
    {
        matrix4 ret(a);
        for (size_t i = 0; i < 16; ++i)
        {
            ret.data[i] *= b;
        }
        return ret;
    }

    matrix4& operator*=(matrix4& a, GLfloat b)
    {
        for (size_t i = 0; i < 16; ++i)
        {
            a.data[i] *= b;
        }
        return a;
    }

    vector4 operator*(const matrix4& a, const vector4& b)
    {
        return vector4(a.data[ 0] * b.data[ 0] + a.data[ 4] * b.data[ 1] + a.data[ 8] * b.data[ 2] + a.data[12] * b.data[ 3],
                       a.data[ 1] * b.data[ 0] + a.data[ 5] * b.data[ 1] + a.data[ 9] * b.data[ 2] + a.data[13] * b.data[ 3],
                       a.data[ 2] * b.data[ 0] + a.data[ 6] * b.data[ 1] + a.data[10] * b.data[ 2] + a.data[14] * b.data[ 3],
                       a.data[ 3] * b.data[ 0] + a.data[ 7] * b.data[ 1] + a.data[11] * b.data[ 2] + a.data[15] * b.data[ 3]);
    }

    bool operator==(const matrix4& a, const matrix4& b)
    {
        return a.data[ 0] == b.data[ 0] && a.data[ 1] == b.data[ 1] && a.data[ 2] == b.data[ 2] && a.data[ 3] == b.data[ 3] &&
               a.data[ 4] == b.data[ 4] && a.data[ 5] == b.data[ 5] && a.data[ 6] == b.data[ 6] && a.data[ 7] == b.data[ 7] &&
               a.data[ 8] == b.data[ 8] && a.data[ 9] == b.data[ 9] && a.data[10] == b.data[10] && a.data[11] == b.data[11] &&
               a.data[12] == b.data[12] && a.data[13] == b.data[13] && a.data[14] == b.data[14] && a.data[15] == b.data[15];
    }

    bool operator!=(const matrix4& a, const matrix4& b)
    {
        return !(a == b);
    }
}
