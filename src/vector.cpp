#include "vector.hpp"

namespace fixie
{
    vector3::vector3()
        : x(0.0f)
        , y(0.0f)
        , z(0.0f)
    {
    }

    vector3::vector3(GLfloat X, GLfloat Y, GLfloat Z)
        : x(X)
        , y(Y)
        , z(Z)
    {
    }

    vector3::vector3(const GLfloat data[3])
        : x(data[0])
        , y(data[1])
        , z(data[2])
    {

    }

    vector4::vector4()
        : x(0.0f)
        , y(0.0f)
        , z(0.0f)
        , w(1.0f)
    {
    }

    vector4::vector4(GLfloat X, GLfloat Y, GLfloat Z, GLfloat W)
        : x(X)
        , y(Y)
        , z(Z)
        , w(W)
    {
    }

    vector4::vector4(const GLfloat data[4])
        : x(data[0])
        , y(data[1])
        , z(data[2])
        , w(data[3])
    {
    }
}
