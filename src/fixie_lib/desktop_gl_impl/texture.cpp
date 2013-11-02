#include "fixie_lib/desktop_gl_impl/texture.hpp"

#include "fixie/fixie_gl_es.h"

namespace fixie
{
    namespace desktop_gl_impl
    {
        texture::texture(std::shared_ptr<const gl_functions> functions)
            : _functions(functions)
        {
            gl_call(_functions, gl_gen_textures, 1, &_id);
        }

        texture::~texture()
        {
            gl_call_nothrow(_functions, gl_delete_textures, 1, &_id);
        }

        GLuint texture::id() const
        {
            return _id;
        }

        void texture::set_data(GLint level, GLenum internal_format, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels)
        {
            gl_call(_functions, gl_bind_texture, GL_TEXTURE_2D, _id);
            gl_call(_functions, gl_tex_image_2d, GL_TEXTURE_2D, level, internal_format, width, height, 0, format, type, pixels);
        }

        void texture::set_sub_data(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels)
        {
            gl_call(_functions, gl_bind_texture, GL_TEXTURE_2D, _id);
            gl_call(_functions, gl_tex_sub_image_2d, GL_TEXTURE_2D, level, xoffset, yoffset, width, height, format, type, pixels);
        }

        void texture::set_compressed_data(GLint level, GLenum internal_format, GLsizei width, GLsizei height, GLsizei image_size, const GLvoid *data)
        {
            gl_call(_functions, gl_bind_texture, GL_TEXTURE_2D, _id);
            gl_call(_functions, gl_compressed_tex_image_2d, GL_TEXTURE_2D, level, internal_format, width, height, 0, image_size, data);
        }

        void texture::set_compressed_sub_data(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei image_size, const GLvoid *data)
        {
            gl_call(_functions, gl_bind_texture, GL_TEXTURE_2D, _id);
            gl_call(_functions, gl_tex_sub_image_2d, GL_TEXTURE_2D, level, xoffset, yoffset, width, height, format, image_size, data);
        }

        void texture::copy_data(GLint level, GLenum internal_format, GLint x, GLint y, GLsizei width, GLsizei height, std::weak_ptr<const texture_impl> source)
        {
        }

        void texture::copy_sub_data(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, std::weak_ptr<const texture_impl> source)
        {
        }

        void texture::generate_mipmaps()
        {
            gl_call(_functions, gl_bind_texture, GL_TEXTURE_2D, _id);
            gl_call(_functions, gl_generate_mipmap, GL_TEXTURE_2D);
        }
    }
}
