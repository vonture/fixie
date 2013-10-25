#include "fixie_lib/depth_stencil_state.hpp"

#include "fixie/fixie_gl_es.h"

namespace fixie
{
    depth_stencil_state::depth_stencil_state()
        : _depth_func()
        , _depth_test()
        , _depth_range()
        , _stencil_func()
        , _stencil_ref()
        , _stencil_mask()
        , _stencil_fail_operation()
        , _stencil_pass_depth_fail_operation()
        , _stencil_pass_depth_pass_operation()
    {
    }

    const GLenum& depth_stencil_state::depth_func() const
    {
        return _depth_func;
    }

    GLenum& depth_stencil_state::depth_func()
    {
        return _depth_func;
    }

    const GLboolean& depth_stencil_state::depth_test() const
    {
        return _depth_test;
    }

    GLboolean& depth_stencil_state::depth_test()
    {
        return _depth_test;
    }

    const GLboolean& depth_stencil_state::depth_mask() const
    {
        return _depth_mask;
    }

    GLboolean& depth_stencil_state::depth_mask()
    {
        return _depth_mask;
    }

    const fixie::range& depth_stencil_state::depth_range() const
    {
        return _depth_range;
    }

    fixie::range& depth_stencil_state::depth_range()
    {
        return _depth_range;
    }

    const GLenum& depth_stencil_state::stencil_func() const
    {
        return _stencil_func;
    }

    GLenum& depth_stencil_state::stencil_func()
    {
        return _stencil_func;
    }

    const GLint& depth_stencil_state::stencil_ref() const
    {
        return _stencil_ref;
    }

    GLint& depth_stencil_state::stencil_ref()
    {
        return _stencil_ref;
    }

    const GLuint& depth_stencil_state::stencil_mask() const
    {
        return _stencil_mask;
    }

    GLuint& depth_stencil_state::stencil_mask()
    {
        return _stencil_mask;
    }

    const GLenum& depth_stencil_state::stencil_fail_operation() const
    {
        return _stencil_fail_operation;
    }

    GLenum& depth_stencil_state::stencil_fail_operation()
    {
        return _stencil_fail_operation;
    }

    const GLenum& depth_stencil_state::stencil_pass_depth_fail_operation() const
    {
        return _stencil_pass_depth_fail_operation;
    }

    GLenum& depth_stencil_state::stencil_pass_depth_fail_operation()
    {
        return _stencil_pass_depth_fail_operation;
    }

    const GLenum& depth_stencil_state::stencil_pass_depth_pass_operation() const
    {
        return _stencil_pass_depth_pass_operation;
    }

    GLenum& depth_stencil_state::stencil_pass_depth_pass_operation()
    {
        return _stencil_pass_depth_pass_operation;
    }

    fixie::depth_stencil_state get_default_depth_stencil_state()
    {
        depth_stencil_state state;
        state.depth_func() = GL_LESS;
        state.depth_test() = GL_FALSE;
        state.depth_mask() = GL_TRUE;
        state.depth_range() = range(0.0f, 1.0f);
        state.stencil_func() = GL_ALWAYS;
        state.stencil_ref() = 0;
        state.stencil_mask() = static_cast<GLuint>(-1);
        state.stencil_fail_operation() = GL_KEEP;
        state.stencil_pass_depth_fail_operation() = GL_KEEP;
        state.stencil_pass_depth_pass_operation() = GL_KEEP;
        return state;
    }
}
