#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

#include <vector>
#include <memory>

#include "fixie/fixie_gl_types.h"
#include "fixie_lib/sampler_state.hpp"
#include "fixie_lib/noncopyable.hpp"

namespace fixie
{
    class texture_impl : public noncopyable
    {
    public:
        virtual void set_data(GLint level, GLenum internal_format, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels) = 0;
        virtual void set_sub_data(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels) = 0;
        virtual void set_compressed_data(GLint level, GLenum internal_format, GLsizei width, GLsizei height, GLsizei image_size, const GLvoid *data) = 0;
        virtual void set_compressed_sub_data(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei image_size, const GLvoid *data) = 0;
        virtual void set_storage(GLsizei levels, GLenum internal_format, GLsizei width, GLsizei height) = 0;
        virtual void copy_data(GLint level, GLenum internal_format, GLint x, GLint y, GLsizei width, GLsizei height, std::weak_ptr<const texture_impl> source) = 0;
        virtual void copy_sub_data(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, std::weak_ptr<const texture_impl> source) = 0;
        virtual void generate_mipmaps() = 0;
    };

    class texture : public noncopyable
    {
    public:
        explicit texture(std::unique_ptr<texture_impl> impl);

        fixie::sampler_state& sampler_state();
        const fixie::sampler_state& sampler_state() const;

        GLboolean& auto_generate_mipmap();
        const GLboolean& auto_generate_mipmap() const;

        size_t mip_levels() const;
        GLsizei mip_level_width(size_t mip) const;
        GLsizei mip_level_height(size_t mip) const;
        GLboolean mip_level_compressed(size_t mip) const;
        GLenum mip_level_internal_format(size_t mip) const;
        GLboolean immutable() const;
        GLboolean complete() const;

        void set_data(GLint level, GLenum internal_format, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);
        void set_sub_data(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);
        void set_compressed_data(GLint level, GLenum internal_format, GLsizei width, GLsizei height, GLsizei image_size, const GLvoid *data);
        void set_compressed_sub_data(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei image_size, const GLvoid *data);
        void set_storage(GLsizei levels, GLenum internal_format, GLsizei width, GLsizei height);
        void copy_data(GLint level, GLenum internal_format, GLint x, GLint y, GLsizei width, GLsizei height, std::weak_ptr<const texture> source);
        void copy_sub_data(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, std::weak_ptr<const texture> source);

        void generate_mipmaps();

        std::weak_ptr<texture_impl> impl();
        std::weak_ptr<const texture_impl> impl() const;

    private:
        fixie::sampler_state _sampler_state;
        GLboolean _auto_generate_mipmap;

        GLboolean _immutable;

        struct mip_info
        {
            mip_info();

            GLenum internal_format;
            GLsizei width;
            GLsizei height;

            GLboolean compressed;
        };
        std::vector<mip_info> _mips;

        size_t required_mip_levels(GLsizei width, GLsizei height) const;

        std::shared_ptr<texture_impl> _impl;
    };
}

#endif // _TEXTURE_HPP_
