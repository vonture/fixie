#ifndef _FIXIE_LIB_VECTOR_HPP_
#define _FIXIE_LIB_VECTOR_HPP_

#include <cstddef>
#include <array>
#include "fixie/fixie_gl_types.h"

namespace fixie
{
    class vector3
    {
    public:
        vector3();
        vector3(GLfloat x, GLfloat y, GLfloat z);
        explicit vector3(const GLfloat data[3]);

        const GLfloat& x() const;
        GLfloat& x();

        const GLfloat& y() const;
        GLfloat& y();

        const GLfloat& z() const;
        GLfloat& z();

        const GLfloat* data() const;

        const GLfloat& operator()(size_t idx) const;
        GLfloat& operator()(size_t idx);

        static GLfloat length(const vector3& vec);
        static GLfloat length_squared(const vector3& vec);

        static vector3 normalize(const vector3& vec);

        static GLfloat dot(const vector3& a, const vector3& b);
        static vector3 cross(const vector3& a, const vector3& b);

    private:
        std::array<GLfloat, 3> _data;
    };

    bool operator==(const vector3& a, const vector3& b);
    bool operator!=(const vector3& a, const vector3& b);

    class vector4
    {
    public:
        vector4();
        vector4(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
        explicit vector4(const GLfloat data[4]);

        const GLfloat& x() const;
        GLfloat& x();

        const GLfloat& y() const;
        GLfloat& y();

        const GLfloat& z() const;
        GLfloat& z();

        const GLfloat& w() const;
        GLfloat& w();

        const GLfloat* data() const;

        const GLfloat& operator()(size_t idx) const;
        GLfloat& operator()(size_t idx);

        static GLfloat length(const vector4& vec);
        static GLfloat length_squared(const vector4& vec);

        static vector4 normalize(const vector4& vec);

        static GLfloat dot(const vector4& a, const vector4& b);

    private:
        std::array<GLfloat, 4> _data;
    };

    bool operator==(const vector4& a, const vector4& b);
    bool operator!=(const vector4& a, const vector4& b);
}

namespace std
{
    template <>
    struct hash<fixie::vector3> : public std::unary_function<fixie::vector3, size_t>
    {
        size_t operator()(const fixie::vector3& key) const;
    };

    template <>
    struct hash<fixie::vector4> : public std::unary_function<fixie::vector4, size_t>
    {
        size_t operator()(const fixie::vector4& key) const;
    };
}

#endif // _FIXIE_LIB_VECTOR_HPP_
