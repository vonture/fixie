#ifndef _DESKTOP_GL_TEXTURE_HPP_
#define _DESKTOP_GL_TEXTURE_HPP_

#include "texture.hpp"

namespace fixie
{
    namespace desktop_gl_impl
    {
        class texture : public fixie::texture_impl
        {
        public:
            virtual void set_data(GLint level, GLenum internal_format, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels) override;
            virtual void set_sub_data(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels) override;
            virtual void set_compressed_data(GLint level, GLenum internal_format, GLsizei width, GLsizei height, GLsizei image_size, const GLvoid *data) override;
            virtual void set_compressed_sub_data(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei image_size, const GLvoid *data) override;
            virtual void copy_data(GLint level, GLenum internal_format, GLint x, GLint y, GLsizei width, GLsizei height, std::shared_ptr<const texture_impl> source) override;
            virtual void copy_sub_data(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, std::shared_ptr<const texture_impl> source) override;
        };
    }
}

#endif // _DESKTOP_GL_TEXTURE_HPP_
