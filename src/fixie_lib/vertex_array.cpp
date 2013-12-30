#include "fixie_lib/vertex_array.hpp"
#include "fixie_lib/util.hpp"

namespace fixie
{
    vertex_array::vertex_array(size_t texcoord_count)
        : _vertex_attribute()
        , _normal_attribute()
        , _color_attribute()
        , _texcoord_attributes(texcoord_count)
    {
    }

    fixie::vertex_attribute& vertex_array::vertex_attribute()
    {
        return _vertex_attribute;
    }

    const fixie::vertex_attribute& vertex_array::vertex_attribute() const
    {
        return _vertex_attribute;
    }

    fixie::vertex_attribute& vertex_array::normal_attribute()
    {
        return _normal_attribute;
    }

    const fixie::vertex_attribute& vertex_array::normal_attribute() const
    {
        return _normal_attribute;
    }

    fixie::vertex_attribute& vertex_array::color_attribute()
    {
        return _color_attribute;
    }

    const fixie::vertex_attribute& vertex_array::color_attribute() const
    {
        return _color_attribute;
    }

    size_t vertex_array::texcoord_attribute_count() const
    {
        return _texcoord_attributes.size();
    }

    fixie::vertex_attribute& vertex_array::texcoord_attribute(size_t unit)
    {
        return _texcoord_attributes[unit];
    }

    const fixie::vertex_attribute& vertex_array::texcoord_attribute(size_t unit) const
    {
        return _texcoord_attributes[unit];
    }

    fixie::vertex_array get_default_vertex_array(const caps& caps)
    {
        vertex_array vao(caps.max_texture_units());
        vao.vertex_attribute() = default_vertex_attribute();
        vao.normal_attribute() = default_normal_attribute();
        vao.color_attribute() = default_color_attribute();
        for_each_n<size_t>(0U, vao.texcoord_attribute_count(), [&](size_t i){ vao.texcoord_attribute(i) = default_texcoord_attribute(); });
        return vao;
    }

    bool operator==(const vertex_array& a, const vertex_array& b)
    {
        return a.vertex_attribute() == b.vertex_attribute() &&
               a.normal_attribute() == b.normal_attribute() &&
               a.color_attribute() == b.color_attribute() &&
               a.texcoord_attribute_count() == b.texcoord_attribute_count() &&
               equal_n<size_t>(0U, a.texcoord_attribute_count(), [&](size_t i){ return a.texcoord_attribute(i) == b.texcoord_attribute(i); });
    }

    bool operator!=(const vertex_array& a, const vertex_array& b)
    {
        return !(a == b);
    }
}

namespace std
{
    size_t std::hash<fixie::vertex_array>::operator()(const fixie::vertex_array& key) const
    {
        size_t seed = 0;

        fixie::hash_combine(seed, key.vertex_attribute());
        fixie::hash_combine(seed, key.normal_attribute());
        fixie::hash_combine(seed, key.color_attribute());
        fixie::for_each_n<size_t>(0U, key.texcoord_attribute_count(), [&](size_t i){ fixie::hash_combine(seed, key.texcoord_attribute(i)); });

        return seed;
    }
}
