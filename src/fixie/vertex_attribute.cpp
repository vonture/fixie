#include "fixie/vertex_attribute.hpp"

#include "fixie/fixie_gl_es.h"

namespace fixie
{
    vertex_attribute::vertex_attribute()
        : _enabled(GL_FALSE)
        , _size(0)
        , _type(GL_FLOAT)
        , _stride(0)
        , _pointer(nullptr)
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
}
