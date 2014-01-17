#ifndef _FIXIE_LIB_COLOR_BUFFER_STATE_HPP_
#define _FIXIE_LIB_COLOR_BUFFER_STATE_HPP_

#include "fixie/fixie_gl_types.h"

#include "fixie_lib/color.hpp"

namespace fixie
{
    class color_buffer_state
    {
    public:
        color_buffer_state();

        color& clear_color();
        const color& clear_color() const;

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

        const GLboolean& write_mask_red() const;
        GLboolean& write_mask_red();

        const GLboolean& write_mask_green() const;
        GLboolean& write_mask_green();

        const GLboolean& write_mask_blue() const;
        GLboolean& write_mask_blue();

        const GLboolean& write_mask_alpha() const;
        GLboolean& write_mask_alpha();

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

        GLboolean _write_mask_red;
        GLboolean _write_mask_green;
        GLboolean _write_mask_blue;
        GLboolean _write_mask_alpha;
    };

    color_buffer_state default_color_buffer_state();
}

#endif // _FIXIE_LIB_COLOR_BUFFER_STATE_HPP_
