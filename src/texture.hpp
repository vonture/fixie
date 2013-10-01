#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

#include <memory>

#include "fixie_gl_types.h"

namespace fixie
{
    class texture
    {
    public:
        texture();
        virtual ~texture();

        GLenum& wrap_t();
        const GLenum& wrap_t() const;

        GLenum& wrap_s();
        const GLenum& wrap_s() const;

        GLenum& min_filter();
        const GLenum& min_filter() const;

        GLenum& mag_filter();
        const GLenum& mag_filter() const;

        GLboolean& auto_generate_mipmap();
        const GLboolean& auto_generate_mipmap() const;

        virtual void set_data(GLint level, GLenum internalFormat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels) = 0;
        virtual void set_data(GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border, const texture& source) = 0;
        virtual void set_sub_data(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels) = 0;
        virtual void set_sub_data(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const texture& source) = 0;
        virtual void set_compressed_data(GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data) = 0;
        virtual void set_compressed_sub_data(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data) = 0;

        virtual GLboolean complete() = 0;

    private:
        GLenum _wrap_s;
        GLenum _wrap_t;
        GLenum _min_filter;
        GLenum _mag_filter;
        GLboolean _auto_generate_mipmap;
    };
}

#endif // _TEXTURE_HPP_