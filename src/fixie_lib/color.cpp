#include "fixie_lib/color.hpp"
#include "fixie_lib/util.hpp"

namespace fixie
{
    color::color()
    {
        _data[0] = 0.0f;
        _data[1] = 0.0f;
        _data[2] = 0.0f;
        _data[3] = 0.0f;
    }

    color::color(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
    {
        _data[0] = red;
        _data[1] = green;
        _data[2] = blue;
        _data[3] = alpha;
    }

    color::color(const GLfloat data[4])
    {
        _data[0] = data[0];
        _data[1] = data[1];
        _data[2] = data[2];
        _data[3] = data[3];
    }

    const GLfloat& color::r() const
    {
        return _data[0];
    }

    GLfloat& color::r()
    {
        return _data[0];
    }

    const GLfloat& color::g() const
    {
        return _data[1];
    }

    GLfloat& color::g()
    {
        return _data[1];
    }

    const GLfloat& color::b() const
    {
        return _data[2];
    }

    GLfloat& color::b()
    {
        return _data[2];
    }

    const GLfloat& color::a() const
    {
        return _data[3];
    }

    GLfloat& color::a()
    {
        return _data[3];
    }

    const GLfloat* color::data() const
    {
        return _data.data();
    }

    bool operator==(const color& a, const color& b)
    {
        return a.r() == b.r() &&
               a.g() == b.g() &&
               a.b() == b.b() &&
               a.a() == b.a();
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
        fixie::hash_combine(seed, key.r());
        fixie::hash_combine(seed, key.g());
        fixie::hash_combine(seed, key.b());
        fixie::hash_combine(seed, key.a());
        return seed;
    }
}
