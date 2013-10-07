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

        typedef void (GL_APIENTRY gl_gen_buffers_func)(GLsizei n, GLuint* buffers);
        typedef void (GL_APIENTRY gl_delete_buffers_func)(GLsizei n, const GLuint* buffers);
        typedef void (GL_APIENTRY gl_bind_buffer_func)(GLenum target, GLuint buffers);
        typedef void (GL_APIENTRY gl_buffer_data_func)(GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage);
        typedef void (GL_APIENTRY gl_buffer_sub_data_func)(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data);

        typedef void (GL_APIENTRY gl_get_integerv_func)(GLenum pname, GLint *params);
        typedef void (GL_APIENTRY gl_get_floatv_func)(GLenum pname, GLfloat *params);
        typedef GLubyte* (GL_APIENTRY gl_get_string_func)(GLenum name);
        typedef GLubyte* (GL_APIENTRY gl_get_stringi_func)(GLenum name, GLuint index);

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

            std::function<gl_gen_buffers_func> gl_gen_buffers() const;
            std::function<gl_delete_buffers_func> gl_delete_buffers() const;
            std::function<gl_bind_buffer_func> gl_bind_buffer() const;
            std::function<gl_buffer_data_func> gl_buffer_data() const;
            std::function<gl_buffer_sub_data_func> gl_buffer_sub_data() const;

            std::function<gl_get_integerv_func> gl_get_integerv() const;
            std::function<gl_get_floatv_func> gl_get_floatv() const;
            std::function<gl_get_string_func> gl_get_string() const;
            std::function<gl_get_stringi_func> gl_get_stringi() const;

        private:

            std::function<gl_enable_func> _gl_enable;
            std::function<gl_enable_func> _gl_disable;

            std::function<gl_clear_color_func> _gl_clear_color;
            std::function<gl_clear_depthf_func> _gl_clear_depthf;
            std::function<gl_clear_stencil_func> _gl_clear_stencil;
            std::function<gl_clear_func> _gl_clear;

            std::function<gl_scissor_func> _gl_scissor;
            std::function<gl_viewport_func> _gl_viewport;

            std::function<gl_gen_buffers_func> _gl_gen_buffers;
            std::function<gl_delete_buffers_func> _gl_delete_buffers;
            std::function<gl_bind_buffer_func> _gl_bind_buffer;
            std::function<gl_buffer_data_func> _gl_buffer_data;
            std::function<gl_buffer_sub_data_func> _gl_buffer_sub_data;

            std::function<gl_get_integerv_func> _gl_get_integerv;
            std::function<gl_get_floatv_func> _gl_get_floatv;
            std::function<gl_get_string_func> _gl_get_string;
            std::function<gl_get_stringi_func> _gl_get_stringi;
        };
    }
}

#endif // _DESKTOP_GL_FUNCTIONS_HPP_
