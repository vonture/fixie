#ifndef _VERTEX_ATTRIBUTE_HPP_
#define _VERTEX_ATTRIBUTE_HPP_

#include "fixie_gl_types.h"

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

    private:
        GLboolean _enabled;
        GLint _size;
        GLenum _type;
        GLsizei _stride;
        const GLvoid* _pointer;
    };
}

#endif // _VERTEX_ATTRIBUTE_HPP_
