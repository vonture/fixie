#ifndef _COLOR_BUFFER_STATE_HPP_
#define _COLOR_BUFFER_STATE_HPP_

#include "fixie/fixie_gl_types.h"

#include "fixie_lib/color.hpp"

namespace fixie
{
    class color_buffer_state
    {
    public:
        color_buffer_state();

        const GLboolean& alpha_test_enabled() const;
        GLboolean& alpha_test_enabled();

        const GLenum& alpha_test_func() const;
        GLenum& alpha_test_func();

        const GLclampf& alpha_test_ref() const;
        GLclampf& alpha_test_ref();

        const GLboolean& blend_enabled() const;
        GLboolean& blend_enabled();

        const GLenum& blend_src_rgb_func() const;
        GLenum& blend_src_rgb_func();

        const GLenum& blend_dst_rgb_func() const;
        GLenum& blend_dst_rgb_func();

        const GLenum& blend_src_alpha_func() const;
        GLenum& blend_src_alpha_func();

        const GLenum& blend_dst_alpha_func() const;
        GLenum& blend_dst_alpha_func();

        const GLboolean& dither_enabled() const;
        GLboolean& dither_enabled();

        const GLboolean& color_logic_op_enabled() const;
        GLboolean& color_logic_op_enabled();

        const GLenum& color_logic_op_func() const;
        GLenum& color_logic_op_func();

        color& clear_color();
        const color& clear_color() const;

    private:
        color _clear_color;

        GLboolean _alpha_test_enabled;
        GLenum _alpha_test_func;
        GLclampf _alpha_test_ref;

        GLboolean _blend_enabled;
        GLenum _blend_src_rgb_func;
        GLenum _blend_dst_rgb_func;
        GLenum _blend_src_alpha_func;
        GLenum _blend_dst_alpha_func;

        GLboolean _dither_enabled;

        GLboolean _color_logic_op_enabled;
        GLenum _color_logic_op_func;
    };

    color_buffer_state get_default_color_buffer_state();
}

#endif // _COLOR_BUFFER_STATE_HPP_
