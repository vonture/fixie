#ifndef _COLOR_HPP_
#define _COLOR_HPP_

#include "fixie/fixie_gl_types.h"

#include <functional>
#include <cstddef>
#include <array>

namespace fixie
{
    class color
    {
    public:
        color();
        color(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
        color(const GLfloat data[4]);

        const GLfloat& r() const;
        GLfloat& r();

        const GLfloat& g() const;
        GLfloat& g();

        const GLfloat& b() const;
        GLfloat& b();

        const GLfloat& a() const;
        GLfloat& a();

        const GLfloat* data() const;

    private:
        std::array<GLfloat, 4> _data;
    };

    bool operator==(const color& a, const color& b);
    bool operator!=(const color& a, const color& b);
}

namespace std
{
    template <>
    struct hash<fixie::color> : public std::unary_function<fixie::color, size_t>
    {
        size_t operator()(const fixie::color& key) const;
    };
}

#endif // _COLOR_HPP_
