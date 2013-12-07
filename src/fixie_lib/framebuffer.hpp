#ifndef _FRAMEBUFFER_HPP_
#define _FRAMEBUFFER_HPP_

#include <memory>

#include "fixie/fixie_gl_types.h"
#include "fixie_lib/texture.hpp"
#include "fixie_lib/renderbuffer.hpp"
#include "fixie_lib/noncopyable.hpp"
#include "fixie_lib/pixel_store_state.hpp"

namespace fixie
{
    class framebuffer_attachment
    {
    public:
        framebuffer_attachment();
        framebuffer_attachment(std::weak_ptr<const fixie::texture> texture, GLint level, GLsizei samples);
        framebuffer_attachment(std::weak_ptr<const fixie::renderbuffer> renderbuffer);

        GLboolean is_texture() const;
        std::weak_ptr<const fixie::texture> texture() const;
        GLint texture_level() const;
        GLsizei texture_samples() const;

        GLboolean is_renderbuffer() const;
        std::weak_ptr<const fixie::renderbuffer> renderbuffer() const;

        GLboolean is_bound() const;

    private:
        std::shared_ptr<const fixie::texture> _texture;
        GLint _texture_level;
        GLsizei _texture_samples;

        std::shared_ptr<const fixie::renderbuffer> _renderbuffer;
    };

    class framebuffer_impl : public noncopyable
    {
    public:
        virtual void set_color_attachment(const framebuffer_attachment& attachment) = 0;
        virtual void set_depth_attachment(const framebuffer_attachment& attachment) = 0;
        virtual void set_stencil_attachment(const framebuffer_attachment& attachment) = 0;

        virtual GLenum preferred_read_format() const = 0;
        virtual GLenum preferred_read_type() const = 0;
        virtual void read_pixels(const pixel_store_state& store_state, GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* data) = 0;

        virtual GLenum status() const = 0;
    };

    class framebuffer : public noncopyable
    {
    public:
        explicit framebuffer(std::unique_ptr<framebuffer_impl> impl);

        const framebuffer_attachment& color_attachment() const;
        void set_color_attachment(const framebuffer_attachment& attachment);

        const framebuffer_attachment& depth_attachment() const;
        void set_depth_attachment(const framebuffer_attachment& attachment);

        const framebuffer_attachment& stencil_attachment() const;
        void set_stencil_attachment(const framebuffer_attachment& attachment);

        GLenum preferred_read_format() const;
        GLenum preferred_read_type() const;
        void read_pixels(const pixel_store_state& store_state, GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* data);

        GLenum status() const;

        std::weak_ptr<framebuffer_impl> impl();
        std::weak_ptr<const framebuffer_impl> impl() const;

    private:
        framebuffer_attachment _color;
        framebuffer_attachment _depth;
        framebuffer_attachment _stencil;

        std::shared_ptr<framebuffer_impl> _impl;
    };
}

#endif // _FRAMEBUFFER_HPP_
