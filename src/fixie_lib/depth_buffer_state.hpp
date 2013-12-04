#ifndef _DEPTH_STENCIL_STATE_HPP_
#define _DEPTH_STENCIL_STATE_HPP_

#include "fixie/fixie_gl_types.h"

#include "fixie_lib/range.hpp"

namespace fixie
{
    class depth_buffer_state
    {
    public:
        depth_buffer_state();

        const GLenum& depth_func() const;
        GLenum& depth_func();

        const GLboolean& depth_test_enabled() const;
        GLboolean& depth_test_enabled();

        const GLboolean& depth_write_mask() const;
        GLboolean& depth_write_mask();

    private:
        GLboolean _depth_test_enabled;
        GLenum _depth_func;

        GLboolean _depth_write_mask;
    };

    depth_buffer_state get_default_depth_buffer_state();
}

#endif // _DEPTH_STENCIL_STATE_HPP_
