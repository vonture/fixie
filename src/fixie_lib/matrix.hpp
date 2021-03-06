#ifndef _FIXIE_LIB_MATRIX_HPP_
#define _FIXIE_LIB_MATRIX_HPP_

#include "fixie/fixie_gl_types.h"
#include "fixie_lib/vector.hpp"

#include <array>

namespace fixie
{
    class matrix4
    {
    public:
        matrix4();
        matrix4(GLfloat m00, GLfloat m01, GLfloat m02, GLfloat m03,
                GLfloat m10, GLfloat m11, GLfloat m12, GLfloat m13,
                GLfloat m20, GLfloat m21, GLfloat m22, GLfloat m23,
                GLfloat m30, GLfloat m31, GLfloat m32, GLfloat m33);
        explicit matrix4(const GLfloat arr[16]);

        const GLfloat& operator()(size_t row, size_t col) const;
        GLfloat& operator()(size_t row, size_t col);

        const GLfloat* data() const;

        static matrix4 identity();
        static matrix4 rotate(GLfloat angle, const vector3& p);
        static matrix4 translate(const vector3& t);
        static matrix4 scale(const vector3& s);
        static matrix4 frustum(GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
        static matrix4 ortho(GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);

        static matrix4 invert(const matrix4& mat);
        static matrix4 transpose(const matrix4& mat);
        static vector3 transform(const matrix4& mat, const vector3& pt);

    private:
        std::array<GLfloat, 16> _data;
    };

    matrix4 operator*(const matrix4& a, const matrix4& b);
    matrix4& operator*=(matrix4& a, const matrix4& b);
    matrix4 operator*(const matrix4& a, GLfloat b);
    matrix4& operator*=(matrix4& a, GLfloat b);
    vector4 operator*(const matrix4& a, const vector4& b);

    bool operator==(const matrix4& a, const matrix4& b);
    bool operator!=(const matrix4& a, const matrix4& b);
}

#endif // _FIXIE_LIB_MATRIX_HPP_
