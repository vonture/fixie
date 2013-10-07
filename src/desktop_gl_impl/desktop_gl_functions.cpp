#include "desktop_gl_impl/desktop_gl_functions.hpp"

namespace fixie
{
    namespace desktop_gl_impl
    {
        gl_functions::gl_functions()
        {
            _gl_enable = load_gl_function<gl_enable_func>("glEnable");
            _gl_disable = load_gl_function<gl_disable_func>("glDisable");

            _gl_clear_color = load_gl_function<gl_clear_color_func>("glClearColor");
            _gl_clear_depthf = load_gl_function<gl_clear_depthf_func>("glClearDepthf");
            _gl_clear_stencil = load_gl_function<gl_clear_stencil_func>("glClearStencil");
            _gl_clear = load_gl_function<gl_clear_func>("glClear");

            _gl_scissor = load_gl_function<gl_scissor_func>("glScissor");
            _gl_viewport = load_gl_function<gl_viewport_func>("glViewport");

            _gl_gen_buffers = load_gl_function<gl_gen_buffers_func>("glGenBuffers");
            _gl_delete_buffers = load_gl_function<gl_delete_buffers_func>("glDeleteBuffers");
            _gl_bind_buffer = load_gl_function<gl_bind_buffer_func>("glBindBuffer");
            _gl_buffer_data = load_gl_function<gl_buffer_data_func>("glBufferData");
            _gl_buffer_sub_data = load_gl_function<gl_buffer_sub_data_func>("glBufferSubData");

            _gl_get_integerv = load_gl_function<gl_get_integerv_func>("glGetIntegerv");
            _gl_get_floatv = load_gl_function<gl_get_floatv_func>("glGetFloatv");
            _gl_get_string = load_gl_function<gl_get_string_func>("glGetString");
            _gl_get_stringi = load_gl_function<gl_get_stringi_func>("glGetStringi");
        }

        std::function<gl_enable_func> gl_functions::gl_enable() const
        {
            return _gl_enable;
        }

        std::function<gl_disable_func> gl_functions::gl_disable() const
        {
            return _gl_disable;
        }

        std::function<gl_clear_color_func> gl_functions::gl_clear_color() const
        {
            return _gl_clear_color;
        }

        std::function<gl_clear_depthf_func> gl_functions::gl_clear_depthf() const
        {
            return _gl_clear_depthf;
        }

        std::function<gl_clear_stencil_func> gl_functions::gl_clear_stencil() const
        {
            return _gl_clear_stencil;
        }

        std::function<gl_clear_func> gl_functions::gl_clear() const
        {
            return _gl_clear;
        }

        std::function<gl_scissor_func> gl_functions::gl_scissor() const
        {
            return _gl_scissor;
        }

        std::function<gl_viewport_func> gl_functions::gl_viewport() const
        {
            return _gl_viewport;
        }

        std::function<gl_gen_buffers_func> gl_functions::gl_gen_buffers() const
        {
            return _gl_gen_buffers;
        }

        std::function<gl_delete_buffers_func> gl_functions::gl_delete_buffers() const
        {
            return _gl_delete_buffers;
        }

        std::function<gl_bind_buffer_func> gl_functions::gl_bind_buffer() const
        {
            return _gl_bind_buffer;
        }

        std::function<gl_buffer_data_func> gl_functions::gl_buffer_data() const
        {
            return _gl_buffer_data;
        }

        std::function<gl_buffer_sub_data_func> gl_functions::gl_buffer_sub_data() const
        {
            return _gl_buffer_sub_data;
        }

        std::function<gl_get_integerv_func> gl_functions::gl_get_integerv() const
        {
            return _gl_get_integerv;
        }

        std::function<gl_get_floatv_func> gl_functions::gl_get_floatv() const
        {
            return _gl_get_floatv;
        }

        std::function<gl_get_string_func> gl_functions::gl_get_string() const
        {
            return _gl_get_string;
        }

        std::function<gl_get_stringi_func> gl_functions::gl_get_stringi() const
        {
            return _gl_get_stringi;
        }
    }
}
