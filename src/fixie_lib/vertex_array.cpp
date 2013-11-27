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
        vao.vertex_attribute() = get_default_vertex_attribute();
        vao.normal_attribute() = get_default_normal_attribute();
        vao.color_attribute() = get_default_color_attribute();
        for_each_n(0, caps.max_texture_units(), [&](size_t i){ vao.texcoord_attribute(i) = get_default_texcoord_attribute(); });
        return vao;
    }
}
