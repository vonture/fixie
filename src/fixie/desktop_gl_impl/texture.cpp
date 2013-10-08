#include "fixie/desktop_gl_impl/texture.hpp"

namespace fixie
{
    namespace desktop_gl_impl
    {
        texture::texture(std::shared_ptr<gl_functions> functions)
            : _functions(functions)
        {
        }

        void texture::set_data(GLint level, GLenum internal_format, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels)
        {
        }

        void texture::set_sub_data(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels)
        {
        }

        void texture::set_compressed_data(GLint level, GLenum internal_format, GLsizei width, GLsizei height, GLsizei image_size, const GLvoid *data)
        {
        }

        void texture::set_compressed_sub_data(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei image_size, const GLvoid *data)
        {
        }

        void texture::copy_data(GLint level, GLenum internal_format, GLint x, GLint y, GLsizei width, GLsizei height, std::shared_ptr<const texture_impl> source)
        {
        }

        void texture::copy_sub_data(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, std::shared_ptr<const texture_impl> source)
        {
        }
    }
}
