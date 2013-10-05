#ifndef _DESKTOP_GL_FUNCTIONS_HPP_
#define _DESKTOP_GL_FUNCTIONS_HPP_

#include "fixie_gl_types.h"
#include "function_loader.hpp"

namespace fixie
{
    namespace desktop_gl_impl
    {
        typedef void (GL_APIENTRY gl_enable_func)(GLenum cap);
        typedef void (GL_APIENTRY gl_disable_func)(GLenum cap);

        typedef void (GL_APIENTRY gl_clear_color_func)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
        typedef void (GL_APIENTRY gl_clear_depthf_func)(GLclampf depth);
        typedef void (GL_APIENTRY gl_clear_stencil_func)(GLint s);
        typedef void (GL_APIENTRY gl_clear_func)(GLbitfield mask);

        typedef void (GL_APIENTRY gl_scissor_func)(GLint x, GLint y, GLsizei width, GLsizei height);
        typedef void (GL_APIENTRY gl_viewport_func)(GLint x, GLint y, GLsizei width, GLsizei height);

        typedef void (GL_APIENTRY gl_get_integerv_func)(GLenum pname, GLint *params);
        typedef void (GL_APIENTRY gl_get_floatv_func)(GLenum pname, GLfloat *params);

        class gl_functions
        {
        public:
            gl_functions();

            std::function<gl_enable_func> gl_enable() const;
            std::function<gl_disable_func> gl_disable() const;

            std::function<gl_clear_color_func> gl_clear_color() const;
            std::function<gl_clear_depthf_func> gl_clear_depthf() const;
            std::function<gl_clear_stencil_func> gl_clear_stencil() const;
            std::function<gl_clear_func> gl_clear() const;

            std::function<gl_scissor_func> gl_scissor() const;
            std::function<gl_viewport_func> gl_viewport() const;

            std::function<gl_get_integerv_func> gl_get_integerv() const;
            std::function<gl_get_floatv_func> gl_get_floatv() const;

        private:
            std::function<gl_enable_func> _gl_enable;
            std::function<gl_enable_func> _gl_disable;

            std::function<gl_clear_color_func> _gl_clear_color;
            std::function<gl_clear_depthf_func> _gl_clear_depthf;
            std::function<gl_clear_stencil_func> _gl_clear_stencil;
            std::function<gl_clear_func> _gl_clear;

            std::function<gl_scissor_func> _gl_scissor;
            std::function<gl_viewport_func> _gl_viewport;

            std::function<gl_get_integerv_func> _gl_get_integerv;
            std::function<gl_get_floatv_func> _gl_get_floatv;
        };
    }
}

#endif // _DESKTOP_GL_FUNCTIONS_HPP_
