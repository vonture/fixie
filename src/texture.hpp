#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

#include <vector>
#include <memory>

#include "fixie_gl_types.h"

namespace fixie
{
    class texture_impl
    {
    public:
        virtual void set_data(GLint level, GLenum internal_format, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels) = 0;
        virtual void set_sub_data(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels) = 0;
        virtual void set_compressed_data(GLint level, GLenum internal_format, GLsizei width, GLsizei height, GLsizei image_size, const GLvoid *data) = 0;
        virtual void set_compressed_sub_data(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei image_size, const GLvoid *data) = 0;
        virtual void copy_data(GLint level, GLenum internal_format, GLint x, GLint y, GLsizei width, GLsizei height, std::shared_ptr<const texture_impl> source) = 0;
        virtual void copy_sub_data(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, std::shared_ptr<const texture_impl> source) = 0;
    };

    class texture
    {
    public:
        explicit texture(std::shared_ptr<texture_impl> impl);

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

        size_t mip_levels() const;
        GLsizei mip_level_width(size_t mip) const;
        GLsizei mip_level_height(size_t mip) const;
        GLboolean complete() const;

        std::shared_ptr<texture_impl> impl();
        std::shared_ptr<const texture_impl> impl() const;

        void set_data(GLint level, GLenum internal_format, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);
        void set_sub_data(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);
        void set_compressed_data(GLint level, GLenum internal_format, GLsizei width, GLsizei height, GLsizei image_size, const GLvoid *data);
        void set_compressed_sub_data(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei image_size, const GLvoid *data);
        void copy_data(GLint level, GLenum internal_format, GLint x, GLint y, GLsizei width, GLsizei height, const texture& source);
        void copy_sub_data(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const texture& source);

    private:
        GLenum _wrap_s;
        GLenum _wrap_t;
        GLenum _min_filter;
        GLenum _mag_filter;
        GLboolean _auto_generate_mipmap;

        struct mip_info
        {
            GLenum internal_format;
            GLsizei width;
            GLsizei height;

            mip_info();
        };
        std::vector<mip_info> _mips;

        std::shared_ptr<texture_impl> _impl;
    };
}

#endif // _TEXTURE_HPP_
