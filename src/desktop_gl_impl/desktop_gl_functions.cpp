#include "desktop_gl_impl/desktop_gl_functions.hpp"

namespace fixie
{
    namespace desktop_gl_impl
    {
        gl_functions::gl_functions()
        {
            _gl_clear_color = load_gl_function<gl_clear_color_func>("glClearColor");
            _gl_clear_depthf = load_gl_function<gl_clear_depthf_func>("glClearDepthf");
            _gl_clear_stencil = load_gl_function<gl_clear_stencil_func>("glClearStencil");
            _gl_clear = load_gl_function<gl_clear_func>("glClear");
            _gl_scissor = load_gl_function<gl_scissor_func>("glScissor");
            _gl_get_integerv = load_gl_function<gl_get_integerv_func>("glGetIntegerv");
            _gl_get_floatv = load_gl_function<gl_get_floatv_func>("glGetFloatv");
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

        std::function<gl_get_integerv_func> gl_functions::gl_get_integerv() const
        {
            return _gl_get_integerv;
        }

        std::function<gl_get_floatv_func> gl_functions::gl_get_floatv() const
        {
            return _gl_get_floatv;
        }
    }
}
