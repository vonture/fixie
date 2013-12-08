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

        GLclampf& clear_depth();
        const GLclampf& clear_depth() const;

    private:
        GLboolean _depth_test_enabled;
        GLenum _depth_func;

        GLboolean _depth_write_mask;

        GLclampf _clear_depth;
    };

    depth_buffer_state default_depth_buffer_state();
}

#endif // _DEPTH_STENCIL_STATE_HPP_
