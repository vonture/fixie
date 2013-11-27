#ifndef _VERTEX_ARRAY_HPP_
#define _VERTEX_ARRAY_HPP_

#include "fixie_lib/vertex_attribute.hpp"
#include "fixie_lib/caps.hpp"

#include <vector>

namespace fixie
{
    class vertex_array
    {
    public:
        vertex_array(size_t texcoord_count);

        fixie::vertex_attribute& vertex_attribute();
        const fixie::vertex_attribute& vertex_attribute() const;

        fixie::vertex_attribute& normal_attribute();
        const fixie::vertex_attribute& normal_attribute() const;

        fixie::vertex_attribute& color_attribute();
        const fixie::vertex_attribute& color_attribute() const;

        fixie::vertex_attribute& texcoord_attribute(size_t unit);
        const fixie::vertex_attribute& texcoord_attribute(size_t unit) const;

    private:
        fixie::vertex_attribute _vertex_attribute;
        fixie::vertex_attribute _normal_attribute;
        fixie::vertex_attribute _color_attribute;
        std::vector<fixie::vertex_attribute> _texcoord_attributes;
    };

    vertex_array get_default_vertex_array(const caps& caps);
}

#endif //_VERTEX_ARRAY_HPP_
