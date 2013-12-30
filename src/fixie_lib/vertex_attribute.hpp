#ifndef _VERTEX_ATTRIBUTE_HPP_
#define _VERTEX_ATTRIBUTE_HPP_

#include "fixie/fixie_gl_types.h"

#include "fixie_lib/vector.hpp"
#include "fixie_lib/buffer.hpp"

namespace fixie
{
    class vertex_attribute
    {
    public:
        vertex_attribute();

        GLboolean& attribute_enabled();
        const GLboolean& attribute_enabled() const;

        GLint& size();
        const GLint& size() const;

        GLenum& type();
        const GLenum& type() const;

        GLsizei& stride();
        const GLsizei& stride() const;

        const GLvoid*& pointer();
        const GLvoid* const& pointer() const;

        vector4& generic_values();
        const vector4& generic_values() const;

        std::weak_ptr<fixie::buffer>& buffer();
        std::weak_ptr<const fixie::buffer> buffer() const;

    private:
        GLboolean _attribute_enabled;
        GLint _size;
        GLenum _type;
        GLsizei _stride;
        const GLvoid* _pointer;

        vector4 _generic_values;
        std::weak_ptr<fixie::buffer> _buffer;
    };

    bool operator==(const vertex_attribute& a, const vertex_attribute& b);
    bool operator!=(const vertex_attribute& a, const vertex_attribute& b);

    vertex_attribute default_vertex_attribute();
    vertex_attribute default_normal_attribute();
    vertex_attribute default_color_attribute();
    vertex_attribute default_texcoord_attribute();
}

namespace std
{
    template <>
    struct hash<fixie::vertex_attribute> : public std::unary_function<fixie::vertex_attribute, size_t>
    {
        size_t operator()(const fixie::vertex_attribute& key) const;
    };
}

#endif // _VERTEX_ATTRIBUTE_HPP_
