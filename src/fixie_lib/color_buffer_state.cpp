#include "fixie_lib/color_buffer_state.hpp"

#include "fixie/fixie_gl_es.h"

namespace fixie
{
    color_buffer_state::color_buffer_state()
        :  _alpha_test_enabled()
        , _alpha_test_func()
        , _alpha_test_ref()
        , _blend_enabled()
        , _blend_src_rgb_func()
        , _blend_dst_rgb_func()
        , _blend_src_alpha_func()
        , _blend_dst_alpha_func()
        , _dither_enabled()
        , _color_logic_op_enabled()
        , _color_logic_op_func()
        , _clear_color()
    {
    }

    const GLboolean& color_buffer_state::alpha_test_enabled() const
    {
        return _alpha_test_enabled;
    }

    GLboolean& color_buffer_state::alpha_test_enabled()
    {
        return _alpha_test_enabled;
    }

    const GLenum& color_buffer_state::alpha_test_func() const
    {
        return _alpha_test_func;
    }

    GLenum& color_buffer_state::alpha_test_func()
    {
        return _alpha_test_func;
    }

    const GLclampf& color_buffer_state::alpha_test_ref() const
    {
        return _alpha_test_ref;
    }

    GLclampf& color_buffer_state::alpha_test_ref()
    {
        return _alpha_test_ref;
    }

    const GLboolean& color_buffer_state::blend_enabled() const
    {
        return _blend_enabled;
    }

    GLboolean& color_buffer_state::blend_enabled()
    {
        return _blend_enabled;
    }

    const GLenum& color_buffer_state::blend_src_rgb_func() const
    {
        return _blend_src_rgb_func;
    }

    GLenum& color_buffer_state::blend_src_rgb_func()
    {
        return _blend_src_rgb_func;
    }

    const GLenum& color_buffer_state::blend_dst_rgb_func() const
    {
        return _blend_dst_rgb_func;
    }

    GLenum& color_buffer_state::blend_dst_rgb_func()
    {
        return _blend_dst_rgb_func;
    }

    const GLenum& color_buffer_state::blend_src_alpha_func() const
    {
        return _blend_src_alpha_func;
    }

    GLenum& color_buffer_state::blend_src_alpha_func()
    {
        return _blend_src_alpha_func;
    }

    const GLenum& color_buffer_state::blend_dst_alpha_func() const
    {
        return _blend_dst_alpha_func;
    }

    GLenum& color_buffer_state::blend_dst_alpha_func()
    {
        return _blend_dst_alpha_func;
    }

    const GLboolean& color_buffer_state::dither_enabled() const
    {
        return _dither_enabled;
    }

    GLboolean& color_buffer_state::dither_enabled()
    {
        return _dither_enabled;
    }

    const GLboolean& color_buffer_state::color_logic_op_enabled() const
    {
        return _color_logic_op_enabled;
    }

    GLboolean& color_buffer_state::color_logic_op_enabled()
    {
        return _color_logic_op_enabled;
    }

    const GLenum& color_buffer_state::color_logic_op_func() const
    {
        return _color_logic_op_func;
    }

    GLenum& color_buffer_state::color_logic_op_func()
    {
        return _color_logic_op_func;
    }

    color& color_buffer_state::clear_color()
    {
        return _clear_color;
    }

    const color& color_buffer_state::clear_color() const
    {
        return _clear_color;
    }

    color_buffer_state get_default_color_buffer_state()
    {
        color_buffer_state state;
        state.alpha_test_enabled() = GL_FALSE;
        state.alpha_test_func() = GL_ALWAYS;
        state.alpha_test_ref() = 0.0f;
        state.blend_enabled() = GL_FALSE;
        state.blend_src_rgb_func() = GL_ONE;
        state.blend_dst_rgb_func() = GL_ZERO;
        state.blend_src_alpha_func() = GL_ONE;
        state.blend_dst_alpha_func() = GL_ZERO;
        state.dither_enabled() = GL_TRUE;
        state.color_logic_op_enabled() = GL_FALSE;
        state.color_logic_op_func() = GL_COPY;
        state.clear_color() = color(0.0f, 0.0f, 0.0f, 0.0f);
        return state;
    }
}
