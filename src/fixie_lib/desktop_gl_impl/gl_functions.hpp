#ifndef _DESKTOP_GL_FUNCTIONS_HPP_
#define _DESKTOP_GL_FUNCTIONS_HPP_

#include "fixie/fixie_gl_types.h"
#include "fixie/fixie_ext.h"
#include "fixie_lib/function_loader.hpp"
#include "fixie_lib/exceptions.hpp"

#include <assert.h>

#define gl_call_throw(functions_ptr, name, ...) \
    ((functions_ptr)->name()(__VA_ARGS__)); \
    { \
        GLenum error_code = (functions_ptr)->get_error()(); \
        if (error_code != GL_NO_ERROR) \
        { \
            throw_gl_error(error_code, __FILE__, __LINE__); \
        } \
    }

#define gl_call_nothrow(functions_ptr, name, ...) (functions_ptr->name()(__VA_ARGS__))

#if defined BUILD_DEBUG
    #define gl_call(functions_ptr, name, ...) gl_call_throw(functions_ptr, name, __VA_ARGS__)
#else
    #define gl_call(functions_ptr, name, ...) gl_call_nothrow(functions_ptr, name, __VA_ARGS__)
#endif

namespace fixie
{
    namespace desktop_gl_impl
    {
        #define DECLARE_GL_FUNCTION(name, return_type, args, gl_name) \
            public: \
                std::function<return_type GL_APIENTRY ## args> name() const \
                { \
                    if (_##name == nullptr) \
                    { \
                        _##name = load_gl_function<return_type GL_APIENTRY ## args>(#gl_name); \
                        assert(_##name != nullptr); \
                    } \
                    return _##name; \
                } \
            private: \
                mutable std::function<return_type GL_APIENTRY ## args> _##name

        class gl_functions
        {
            DECLARE_GL_FUNCTION(enable, void, (GLenum cap), glEnable);
            DECLARE_GL_FUNCTION(disable, void, (GLenum cap), glDisable);

            DECLARE_GL_FUNCTION(clear_color, void, (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha), glClearColor);
            DECLARE_GL_FUNCTION(clear_depthf, void, (GLclampf depth), glClearDepthf);
            DECLARE_GL_FUNCTION(clear_stencil, void, (GLint s), glClearStencil);
            DECLARE_GL_FUNCTION(clear, void, (GLbitfield mask), glClear);

            DECLARE_GL_FUNCTION(depth_func, void, (GLboolean func), glDepthFunc);
            DECLARE_GL_FUNCTION(depth_range_f, void, (GLfloat nearVal, GLfloat farVal), glDepthRangef);
            DECLARE_GL_FUNCTION(depth_mask, void, (GLboolean flag), glDepthMask);
            DECLARE_GL_FUNCTION(stencil_func, void, (GLenum func, GLint ref, GLuint mask), glStencilFunc);
            DECLARE_GL_FUNCTION(stencil_op, void, (GLenum stencil_fail, GLenum stencil_pass_depth_fail, GLenum stencil_pass_depth_pass), glStencilOp);

            DECLARE_GL_FUNCTION(scissor, void, (GLint x, GLint y, GLsizei width, GLsizei height), glScissor);
            DECLARE_GL_FUNCTION(viewport, void, (GLint x, GLint y, GLsizei width, GLsizei height), glViewport);

            DECLARE_GL_FUNCTION(gen_buffers, void, (GLsizei n, GLuint* buffers), glGenBuffers);
            DECLARE_GL_FUNCTION(delete_buffers, void, (GLsizei n, const GLuint* buffers), glDeleteBuffers);
            DECLARE_GL_FUNCTION(bind_buffer, void, (GLenum target, GLuint buffers), glBindBuffer);
            DECLARE_GL_FUNCTION(buffer_data, void, (GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage), glBufferData);
            DECLARE_GL_FUNCTION(buffer_sub_data, void, (GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data), glBufferSubData);

            DECLARE_GL_FUNCTION(gen_textures, void, (GLsizei n, GLuint* textures), glGenTextures);
            DECLARE_GL_FUNCTION(delete_textures, void, (GLsizei n, const GLuint* textures), glDeleteTextures);
            DECLARE_GL_FUNCTION(active_texture, void, (GLenum texture), glActiveTexture);
            DECLARE_GL_FUNCTION(bind_texture, void, (GLenum target, GLuint texture), glBindTexture);
            DECLARE_GL_FUNCTION(tex_image_2d, void, (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels), glTexImage2D);
            DECLARE_GL_FUNCTION(tex_sub_image_2d, void, (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels), glTexSubImage2D);
            DECLARE_GL_FUNCTION(compressed_tex_image_2d, void, (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data), glCompressedTexImage2D);
            DECLARE_GL_FUNCTION(compressed_tex_sub_image_2d, void, (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data), glCompressedTexSubImage2D);
            DECLARE_GL_FUNCTION(copy_tex_image_2d, void, (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border), glCopyTexImage2D);
            DECLARE_GL_FUNCTION(copy_tex_sub_image_2d, void, (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height), glCopyTexSubImage2D);
            DECLARE_GL_FUNCTION(tex_parameter_i, void, (GLenum target, GLenum pname, GLint param), glTexParameteri);
            DECLARE_GL_FUNCTION(tex_parameter_iv, void, (GLenum target, GLenum pname, const GLint* params), glTexParameteriv);
            DECLARE_GL_FUNCTION(tex_parameter_f, void, (GLenum target, GLenum pname, GLfloat param), glTexParameterf);
            DECLARE_GL_FUNCTION(tex_parameter_fv, void, (GLenum target, GLenum pname, const GLfloat* params), glTexParameterfv);
            DECLARE_GL_FUNCTION(generate_mipmap, void, (GLenum target), glGenerateMipmap);

            DECLARE_GL_FUNCTION(get_integerv, void, (GLenum pname, GLint *params), glGetIntegerv);
            DECLARE_GL_FUNCTION(get_floatv, void, (GLenum pname, GLfloat *params), glGetFloatv);
            DECLARE_GL_FUNCTION(get_string, GLubyte*, (GLenum name), glGetString);
            DECLARE_GL_FUNCTION(get_stringi, GLubyte*, (GLenum name, GLuint index), glGetStringi);
            DECLARE_GL_FUNCTION(get_error, GLenum, (), glGetError);
            DECLARE_GL_FUNCTION(get_framebuffer_attachment_parameter_iv, void, (GLenum target, GLenum attachment, GLenum pname, GLint* params), glGetFramebufferAttachmentParameteriv);

            DECLARE_GL_FUNCTION(create_shader, GLuint, (GLenum shader_type), glCreateShader);
            DECLARE_GL_FUNCTION(delete_shader, void, (GLuint shader), glDeleteShader);
            DECLARE_GL_FUNCTION(shader_source, void, (GLuint shader, GLsizei count, const GLchar** string, const GLint* length), glShaderSource);
            DECLARE_GL_FUNCTION(compile_shader, void, (GLuint shader), glCompileShader);
            DECLARE_GL_FUNCTION(get_shader_iv, void, (GLuint shader, GLenum pname, GLint* params), glGetShaderiv);
            DECLARE_GL_FUNCTION(get_shader_info_log, void, (GLuint shader, GLsizei max_length, GLsizei* length, GLchar* infoLog), glGetShaderInfoLog);

            DECLARE_GL_FUNCTION(create_program, GLuint, (), glCreateProgram);
            DECLARE_GL_FUNCTION(delete_program, void, (GLuint program), glDeleteProgram);
            DECLARE_GL_FUNCTION(use_program, void, (GLuint program), glUseProgram);
            DECLARE_GL_FUNCTION(attach_shader, void, (GLuint program, GLuint shader), glAttachShader);
            DECLARE_GL_FUNCTION(link_program, void, (GLuint program), glLinkProgram);
            DECLARE_GL_FUNCTION(get_program_iv, void, (GLuint program, GLenum pname, GLint* params), glGetProgramiv);
            DECLARE_GL_FUNCTION(get_program_info_log, void, (GLuint program, GLsizei max_length, GLsizei* length, GLchar* infoLog), glGetProgramInfoLog);
            DECLARE_GL_FUNCTION(bind_frag_data_location, void, (GLuint program, GLuint color_number, const GLchar* name), glBindFragDataLocation);

            DECLARE_GL_FUNCTION(get_uniform_location, GLint, (GLuint program, const GLchar* name), glGetUniformLocation);
            DECLARE_GL_FUNCTION(get_attrib_location, GLint, (GLuint program, const GLchar* name), glGetAttribLocation);
            DECLARE_GL_FUNCTION(vertex_attrib_pointer, void, (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer), glVertexAttribPointer);
            DECLARE_GL_FUNCTION(enable_vertex_attrib_array, void, (GLuint index), glEnableVertexAttribArray);
            DECLARE_GL_FUNCTION(disable_vertex_attrib_array, void, (GLuint index), glDisableVertexAttribArray);

            DECLARE_GL_FUNCTION(bind_vertex_array, void, (GLuint array), glBindVertexArray);
            DECLARE_GL_FUNCTION(delete_vertex_arrays, void, (GLsizei n, GLuint* arrays), glDeleteVertexArrays);
            DECLARE_GL_FUNCTION(gen_vertex_arrays, void, (GLsizei n, GLuint* arrays), glGenVertexArrays);
            DECLARE_GL_FUNCTION(is_vertex_array, GLboolean, (GLuint array), glIsVertexArray);

            DECLARE_GL_FUNCTION(vertex_attrib_1f, void, (GLuint index, GLfloat v0), glVertexAttrib1f);
            DECLARE_GL_FUNCTION(vertex_attrib_2f, void, (GLuint index, GLfloat v0, GLfloat v1), glVertexAttrib2f);
            DECLARE_GL_FUNCTION(vertex_attrib_3f, void, (GLuint index, GLfloat v0, GLfloat v1, GLfloat v2), glVertexAttrib3f);
            DECLARE_GL_FUNCTION(vertex_attrib_4f, void, (GLuint index, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3), glVertexAttrib4f);

            DECLARE_GL_FUNCTION(uniform_1f, void, (GLint location, GLfloat v0), glUniform1f);
            DECLARE_GL_FUNCTION(uniform_2f, void, (GLint location, GLfloat v0, GLfloat v1), glUniform2f);
            DECLARE_GL_FUNCTION(uniform_3f, void, (GLint location, GLfloat v0, GLfloat v1, GLfloat v2), glUniform3f);
            DECLARE_GL_FUNCTION(uniform_4f, void, (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3), glUniform4f);
            DECLARE_GL_FUNCTION(uniform_1fv, void, (GLint location, GLsizei count, const GLfloat* value), glUniform1fv);
            DECLARE_GL_FUNCTION(uniform_2fv, void, (GLint location, GLsizei count, const GLfloat* value), glUniform2fv);
            DECLARE_GL_FUNCTION(uniform_3fv, void, (GLint location, GLsizei count, const GLfloat* value), glUniform3fv);
            DECLARE_GL_FUNCTION(uniform_4fv, void, (GLint location, GLsizei count, const GLfloat* value), glUniform4fv);

            DECLARE_GL_FUNCTION(uniform_1i, void, (GLint location, GLint v0), glUniform1i);
            DECLARE_GL_FUNCTION(uniform_2i, void, (GLint location, GLint v0, GLint v1), glUniform2i);
            DECLARE_GL_FUNCTION(uniform_3i, void, (GLint location, GLint v0, GLint v1, GLint v2), glUniform3i);
            DECLARE_GL_FUNCTION(uniform_4i, void, (GLint location, GLint v0, GLint v1, GLint v2, GLint v3), glUniform4i);
            DECLARE_GL_FUNCTION(uniform_1iv, void, (GLint location, GLsizei count, const GLint* value), glUniform1iv);
            DECLARE_GL_FUNCTION(uniform_2iv, void, (GLint location, GLsizei count, const GLint* value), glUniform2iv);
            DECLARE_GL_FUNCTION(uniform_3iv, void, (GLint location, GLsizei count, const GLint* value), glUniform3iv);
            DECLARE_GL_FUNCTION(uniform_4iv, void, (GLint location, GLsizei count, const GLint* value), glUniform4iv);

            DECLARE_GL_FUNCTION(uniform_1ui, void, (GLint location, GLuint v0), glUniform1ui);
            DECLARE_GL_FUNCTION(uniform_2ui, void, (GLint location, GLuint v0, GLuint v1), glUniform2ui);
            DECLARE_GL_FUNCTION(uniform_3ui, void, (GLint location, GLuint v0, GLuint v1, GLuint v2), glUniform3ui);
            DECLARE_GL_FUNCTION(uniform_4ui, void, (GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3), glUniform4ui);
            DECLARE_GL_FUNCTION(uniform_1uiv, void, (GLint location, GLsizei count, const GLuint* value), glUniform1uiv);
            DECLARE_GL_FUNCTION(uniform_2uiv, void, (GLint location, GLsizei count, const GLuint* value), glUniform2uiv);
            DECLARE_GL_FUNCTION(uniform_3uiv, void, (GLint location, GLsizei count, const GLuint* value), glUniform3uiv);
            DECLARE_GL_FUNCTION(uniform_4uiv, void, (GLint location, GLsizei count, const GLuint* value), glUniform4uiv);

            DECLARE_GL_FUNCTION(uniform_matrix_2fv, void, (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value), glUniformMatrix2fv);
            DECLARE_GL_FUNCTION(uniform_matrix_3fv, void, (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value), glUniformMatrix3fv);
            DECLARE_GL_FUNCTION(uniform_matrix_4fv, void, (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value), glUniformMatrix4fv);
            DECLARE_GL_FUNCTION(uniform_matrix_2x3fv, void, (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value), glUniformMatrix2x3fv);
            DECLARE_GL_FUNCTION(uniform_matrix_3x2fv, void, (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value), glUniformMatrix3x2fv);
            DECLARE_GL_FUNCTION(uniform_matrix_2x4fv, void, (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value), glUniformMatrix2x4fv);
            DECLARE_GL_FUNCTION(uniform_matrix_4x2fv, void, (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value), glUniformMatrix4x2fv);
            DECLARE_GL_FUNCTION(uniform_matrix_3x4fv, void, (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value), glUniformMatrix3x4fv);
            DECLARE_GL_FUNCTION(uniform_matrix_4x3fv, void, (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value), glUniformMatrix4x3fv);

            DECLARE_GL_FUNCTION(draw_arrays, void, (GLenum mode, GLint first, GLsizei count), glDrawArrays);
            DECLARE_GL_FUNCTION(draw_elements, void, (GLenum mode, GLsizei count, GLenum type, const GLvoid* indices), glDrawElements);

            DECLARE_GL_FUNCTION(debug_message_control, void, (GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint* ids, GLboolean enabled), glDebugMessageControl);
            DECLARE_GL_FUNCTION(debug_message_callback, void, (GLDEBUGPROC callback, const GLvoid* userParam), glDebugMessageCallback);
        };

        #undef DECLARE_GL_FUNCTION
    }
}

#endif // _DESKTOP_GL_FUNCTIONS_HPP_
