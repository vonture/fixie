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

        GLboolean& enabled();
        const GLboolean& enabled() const;

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
        GLboolean _enabled;
        GLint _size;
        GLenum _type;
        GLsizei _stride;
        const GLvoid* _pointer;

        vector4 _generic_values;
        std::weak_ptr<fixie::buffer> _buffer;
    };

    vertex_attribute get_default_vertex_attribute();
    vertex_attribute get_default_normal_attribute();
    vertex_attribute get_default_color_attribute();
    vertex_attribute get_default_texcoord_attribute();
}

#endif // _VERTEX_ATTRIBUTE_HPP_
