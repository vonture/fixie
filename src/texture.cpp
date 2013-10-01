#include "texture.hpp"

#include "fixie_gl_es.h"

#include <assert.h>

namespace fixie
{
    texture::texture()
        : _wrap_s(GL_REPEAT)
        , _wrap_t(GL_REPEAT)
        , _min_filter(GL_NEAREST_MIPMAP_LINEAR)
        , _mag_filter(GL_LINEAR)
        , _auto_generate_mipmap(GL_FALSE)
    {
    }

    texture::~texture()
    {
    }

    GLenum& texture::wrap_t()
    {
        return _wrap_t;
    }

    const GLenum& texture::wrap_t() const
    {
        return _wrap_t;
    }

    GLenum& texture::wrap_s()
    {
        return _wrap_s;
    }

    const GLenum& texture::wrap_s() const
    {
        return _wrap_s;
    }

    GLenum& texture::min_filter()
    {
        return _min_filter;
    }

    const GLenum& texture::min_filter() const
    {
        return _min_filter;
    }

    GLenum& texture::mag_filter()
    {
        return _mag_filter;
    }

    const GLenum& texture::mag_filter() const
    {
        return _mag_filter;
    }

    GLboolean& texture::auto_generate_mipmap()
    {
        return _auto_generate_mipmap;
    }

    const GLboolean& texture::auto_generate_mipmap() const
    {
        return _auto_generate_mipmap;
    }
}
