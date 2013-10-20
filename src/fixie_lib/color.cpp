#include "fixie_lib/color.hpp"
#include "fixie_lib/util.hpp"

namespace fixie
{
    color::color()
        : r(0.0f)
        , g(0.0f)
        , b(0.0f)
        , a(1.0f)
    {
    }

    color::color(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
        : r(red)
        , g(green)
        , b(blue)
        , a(alpha)
    {
    }

    color::color(const GLfloat data[4])
        : r(data[0])
        , g(data[1])
        , b(data[2])
        , a(data[3])
    {
    }

    bool operator==(const color& a, const color& b)
    {
        return a.r == b.r &&
               a.g == b.g &&
               a.b == b.b &&
               a.a == b.a;
    }

    bool operator!=(const color& a, const color& b)
    {
        return !(a == b);
    }
}

namespace std
{
    size_t hash<fixie::color>::operator()(const fixie::color& key) const
    {
        size_t seed = 0;
        fixie::hash_combine(seed, key.r);
        fixie::hash_combine(seed, key.g);
        fixie::hash_combine(seed, key.b);
        fixie::hash_combine(seed, key.a);
        return seed;
    }
}
