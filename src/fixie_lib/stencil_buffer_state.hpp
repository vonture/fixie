#ifndef _STENCIL_BUFFER_STATE_HPP_
#define _STENCIL_BUFFER_STATE_HPP_

#include "fixie/fixie_gl_types.h"

#include "fixie_lib/range.hpp"

namespace fixie
{
    class stencil_buffer_state
    {
    public:
        stencil_buffer_state();

        const GLboolean& stencil_test_enabled() const;
        GLboolean& stencil_test_enabled();

        const GLenum& stencil_func() const;
        GLenum& stencil_func();

        const GLuint& stencil_read_mask() const;
        GLuint& stencil_read_mask();

        const GLint& stencil_ref() const;
        GLint& stencil_ref();

        const GLenum& stencil_fail_operation() const;
        GLenum& stencil_fail_operation();

        const GLenum& stencil_pass_depth_fail_operation() const;
        GLenum& stencil_pass_depth_fail_operation();

        const GLenum& stencil_pass_depth_pass_operation() const;
        GLenum& stencil_pass_depth_pass_operation();

        const GLuint& stencil_write_mask() const;
        GLuint& stencil_write_mask();

        GLint& clear_stencil();
        const GLint& clear_stencil() const;

    private:
        GLboolean _stencil_test_enabled;
        GLenum _stencil_func;
        GLint _stencil_ref;
        GLuint _stencil_read_mask;
        GLenum _stencil_fail_operation;
        GLenum _stencil_pass_depth_fail_operation;
        GLenum _stencil_pass_depth_pass_operation;

        GLuint _stencil_write_mask;

        GLint _clear_stencil;
    };

    stencil_buffer_state get_default_stencil_buffer_state();
}

#endif // _STENCIL_BUFFER_STATE_HPP_
