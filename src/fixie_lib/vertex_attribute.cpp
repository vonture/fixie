#include "fixie_lib/vertex_attribute.hpp"
#include "fixie_lib/util.hpp"

#include "fixie/fixie_gl_es.h"

namespace fixie
{
    vertex_attribute::vertex_attribute()
        : _enabled(GL_FALSE)
        , _size(0)
        , _type(GL_FLOAT)
        , _stride(0)
        , _pointer(nullptr)
        , _generic_values(0.0f, 0.0f, 0.0f, 1.0f)
        , _buffer()
    {
    }

    GLboolean& vertex_attribute::enabled()
    {
        return _enabled;
    }

    const GLboolean& vertex_attribute::enabled() const
    {
        return _enabled;
    }

    GLint& vertex_attribute::size()
    {
        return _size;
    }

    const GLint& vertex_attribute::size() const
    {
        return _size;
    }

    GLenum& vertex_attribute::type()
    {
        return _type;
    }

    const GLenum& vertex_attribute::type() const
    {
        return _type;
    }

    GLsizei& vertex_attribute::stride()
    {
        return _stride;
    }

    const GLsizei& vertex_attribute::stride() const
    {
        return _stride;
    }

    const GLvoid*& vertex_attribute::pointer()
    {
        return _pointer;
    }

    const GLvoid* const& vertex_attribute::pointer() const
    {
        return _pointer;
    }

    vector4& vertex_attribute::generic_values()
    {
        return _generic_values;
    }

    const vector4& vertex_attribute::generic_values() const
    {
        return _generic_values;
    }

    std::weak_ptr<fixie::buffer>& vertex_attribute::buffer()
    {
        return _buffer;
    }

    std::weak_ptr<const fixie::buffer> vertex_attribute::buffer() const
    {
        return _buffer;
    }

    static vertex_attribute get_default_common_attribute()
    {
        vertex_attribute attribute;
        attribute.enabled() = GL_FALSE;
        attribute.size() = 0;
        attribute.type() = GL_FALSE;
        attribute.stride() = 0;
        attribute.pointer() = nullptr;
        attribute.generic_values() = vector4(0.0f, 0.0f, 0.0f, 1.0f);
        attribute.buffer().reset();
        return attribute;
    }

    vertex_attribute get_default_vertex_attribute()
    {
        vertex_attribute attribute = get_default_common_attribute();
        attribute.generic_values() = vector4(0.0f, 0.0f, 0.0f, 0.0f);
        return attribute;
    }

    vertex_attribute get_default_normal_attribute()
    {
        vertex_attribute attribute = get_default_common_attribute();
        attribute.generic_values() = vector4(0.0f, 0.0f, 1.0f, 1.0f);
        return attribute;
    }

    vertex_attribute get_default_color_attribute()
    {
        vertex_attribute attribute = get_default_common_attribute();
        attribute.generic_values() = vector4(1.0f, 1.0f, 1.0f, 1.0f);
        return attribute;
    }

    vertex_attribute get_default_texcoord_attribute()
    {
        vertex_attribute attribute = get_default_common_attribute();
        attribute.generic_values() = vector4(0.0f, 0.0f, 0.0f, 1.0f);
        return attribute;
    }

    bool operator==(const vertex_attribute& a, const vertex_attribute& b)
    {
        return a.enabled() == b.enabled() &&
               a.size() == b.size() &&
               a.type() == b.type() &&
               a.stride() == b.stride() &&
               a.pointer() == b.pointer() &&
               a.generic_values() == b.generic_values() &&
               a.buffer().lock() == b.buffer().lock();
    }

    bool operator!=(const vertex_attribute& a, const vertex_attribute& b)
    {
        return !(a == b);
    }
}

namespace std
{
    size_t std::hash<fixie::vertex_attribute>::operator()(const fixie::vertex_attribute& key) const
    {
        size_t seed = 0;

        fixie::hash_combine(seed, key.enabled());
        if (key.enabled())
        {
            fixie::hash_combine(seed, key.size());
            fixie::hash_combine(seed, key.type());
            fixie::hash_combine(seed, key.stride());
            fixie::hash_combine(seed, key.pointer());
            fixie::hash_combine(seed, key.generic_values());
            fixie::hash_combine(seed, key.buffer().lock());
        }

        return seed;
    }
}
