#ifndef _DEPTH_STENCIL_STATE_HPP_
#define _DEPTH_STENCIL_STATE_HPP_

#include "fixie/fixie_gl_types.h"

#include "fixie_lib/range.hpp"

namespace fixie
{
    class depth_stencil_state
    {
    public:
        depth_stencil_state();

        const GLenum& depth_func() const;
        GLenum& depth_func();

        const GLboolean& depth_test() const;
        GLboolean& depth_test();

        const GLboolean& depth_mask() const;
        GLboolean& depth_mask();

        const fixie::range& depth_range() const;
        fixie::range& depth_range();

        const GLenum& stencil_func() const;
        GLenum& stencil_func();

        const GLint& stencil_ref() const;
        GLint& stencil_ref();

        const GLuint& stencil_mask() const;
        GLuint& stencil_mask();

        const GLenum& stencil_fail_operation() const;
        GLenum& stencil_fail_operation();

        const GLenum& stencil_pass_depth_fail_operation() const;
        GLenum& stencil_pass_depth_fail_operation();

        const GLenum& stencil_pass_depth_pass_operation() const;
        GLenum& stencil_pass_depth_pass_operation();

    private:
        GLenum _depth_func;
        GLboolean _depth_test;
        GLboolean _depth_mask;
        range _depth_range;

        GLenum _stencil_func;
        GLint _stencil_ref;
        GLuint _stencil_mask;
        GLenum _stencil_fail_operation;
        GLenum _stencil_pass_depth_fail_operation;
        GLenum _stencil_pass_depth_pass_operation;
    };

    depth_stencil_state get_default_depth_stencil_state();
}

#endif // _DEPTH_STENCIL_STATE_HPP_
