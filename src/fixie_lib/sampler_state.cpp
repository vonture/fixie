#include "fixie_lib/sampler_state.hpp"

#include "fixie/fixie_gl_es.h"

namespace fixie
{
    sampler_state::sampler_state()
        : _wrap_t()
        , _wrap_s()
        , _min_filter()
        , _mag_filter()
    {
    }

    GLenum& sampler_state::wrap_t()
    {
        return _wrap_t;
    }

    const GLenum& sampler_state::wrap_t() const
    {
        return _wrap_t;
    }

    GLenum& sampler_state::wrap_s()
    {
        return _wrap_s;
    }

    const GLenum& sampler_state::wrap_s() const
    {
        return _wrap_s;
    }

    GLenum& sampler_state::min_filter()
    {
        return _min_filter;
    }

    const GLenum& sampler_state::min_filter() const
    {
        return _min_filter;
    }

    GLenum& sampler_state::mag_filter()
    {
        return _mag_filter;
    }

    const GLenum& sampler_state::mag_filter() const
    {
        return _mag_filter;
    }

    sampler_state get_default_sampler_state()
    {
        sampler_state sampler;

        sampler.wrap_s() = GL_REPEAT;
        sampler.wrap_t() = GL_REPEAT;
        sampler.min_filter() = GL_NEAREST_MIPMAP_LINEAR;
        sampler.mag_filter() = GL_LINEAR;

        return sampler;
    }
}
