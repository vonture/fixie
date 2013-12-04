#include "fixie_lib/stencil_buffer_state.hpp"

#include "fixie/fixie_gl_es.h"

namespace fixie
{
    stencil_buffer_state::stencil_buffer_state()
        : _stencil_test_enabled()
        , _stencil_func()
        , _stencil_ref()
        , _stencil_read_mask()
        , _stencil_fail_operation()
        , _stencil_pass_depth_fail_operation()
        , _stencil_pass_depth_pass_operation()
        , _stencil_write_mask()
    {
    }

    const GLboolean& stencil_buffer_state::stencil_test_enabled() const
    {
        return _stencil_test_enabled;
    }

    GLboolean& stencil_buffer_state::stencil_test_enabled()
    {
        return _stencil_test_enabled;
    }

    const GLenum& stencil_buffer_state::stencil_func() const
    {
        return _stencil_func;
    }

    GLenum& stencil_buffer_state::stencil_func()
    {
        return _stencil_func;
    }

    const GLint& stencil_buffer_state::stencil_ref() const
    {
        return _stencil_ref;
    }

    GLint& stencil_buffer_state::stencil_ref()
    {
        return _stencil_ref;
    }

    const GLuint& stencil_buffer_state::stencil_read_mask() const
    {
        return _stencil_read_mask;
    }

    GLuint& stencil_buffer_state::stencil_read_mask()
    {
        return _stencil_read_mask;
    }

    const GLenum& stencil_buffer_state::stencil_fail_operation() const
    {
        return _stencil_fail_operation;
    }

    GLenum& stencil_buffer_state::stencil_fail_operation()
    {
        return _stencil_fail_operation;
    }

    const GLenum& stencil_buffer_state::stencil_pass_depth_fail_operation() const
    {
        return _stencil_pass_depth_fail_operation;
    }

    GLenum& stencil_buffer_state::stencil_pass_depth_fail_operation()
    {
        return _stencil_pass_depth_fail_operation;
    }

    const GLenum& stencil_buffer_state::stencil_pass_depth_pass_operation() const
    {
        return _stencil_pass_depth_pass_operation;
    }

    GLenum& stencil_buffer_state::stencil_pass_depth_pass_operation()
    {
        return _stencil_pass_depth_pass_operation;
    }

    const GLuint& stencil_buffer_state::stencil_write_mask() const
    {
        return _stencil_write_mask;
    }

    GLuint& stencil_buffer_state::stencil_write_mask()
    {
        return _stencil_write_mask;
    }

    stencil_buffer_state get_default_stencil_buffer_state()
    {
        stencil_buffer_state state;
        state.stencil_test_enabled() = GL_FALSE;
        state.stencil_func() = GL_ALWAYS;
        state.stencil_ref() = 0;
        state.stencil_read_mask() = static_cast<GLuint>(-1);
        state.stencil_fail_operation() = GL_KEEP;
        state.stencil_pass_depth_fail_operation() = GL_KEEP;
        state.stencil_pass_depth_pass_operation() = GL_KEEP;
        state.stencil_write_mask() = static_cast<GLuint>(-1);
        return state;
    }
}
