#ifndef _SAMPLER_STATE_HPP_
#define _SAMPLER_STATE_HPP_

#include "fixie/fixie_gl_types.h"

namespace fixie
{
    class sampler_state
    {
    public:
        sampler_state();

        GLenum& wrap_t();
        const GLenum& wrap_t() const;

        GLenum& wrap_s();
        const GLenum& wrap_s() const;

        GLenum& min_filter();
        const GLenum& min_filter() const;

        GLenum& mag_filter();
        const GLenum& mag_filter() const;

    private:
        GLenum _wrap_s;
        GLenum _wrap_t;
        GLenum _min_filter;
        GLenum _mag_filter;
    };

    sampler_state get_default_sampler_state();
}

#endif // _SAMPLER_STATE_HPP_
