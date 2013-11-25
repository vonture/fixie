#include "fixie_lib/framebuffer.hpp"

namespace fixie
{
    framebuffer_attachment::framebuffer_attachment()
        : _texture(nullptr)
        //, _renderbuffer(nullptr)
    {
    }

    GLboolean framebuffer_attachment::is_texture() const
    {
        return _texture != nullptr;
    }

    std::weak_ptr<const fixie::texture> framebuffer_attachment::texture() const
    {
        return _texture;
    }

    void framebuffer_attachment::set(std::weak_ptr<const fixie::texture> texture)
    {
        _texture = texture.lock();
        //_renderbuffer = nullptr;
    }

    /*
    GLboolean framebuffer_attachment::is_renderbuffer() const
    {
        return _renderbuffer != nullptr;
    }
    
    std::weak_ptr<const fixie::renderbuffer> framebuffer_attachment::renderbuffer() const
    {
        return _renderbuffer;
    }

    void framebuffer_attachment::set(std::weak_ptr<const fixie::renderbuffer> renderbuffer)
    {
        _texture = nullptr;
        _renderbuffer = renderbuffer.lock();
    }
    */

    GLboolean framebuffer_attachment::is_bound() const
    {
        return is_texture();// || is_renderbuffer();
    }

    framebuffer::framebuffer(std::unique_ptr<framebuffer_impl> impl)
        : _color()
        , _depth()
        , _stencil()
        , _impl(std::move(impl))
    {
    }

    const framebuffer_attachment& framebuffer::color_attachment() const
    {
        return _color;
    }

    void framebuffer::set_color_attachment(const framebuffer_attachment& attachment)
    {
        _color = attachment;
        _impl->set_color_attachment(_color);
    }

    const framebuffer_attachment& framebuffer::depth_attachment() const
    {
        return _depth;
    }

    void framebuffer::set_depth_attachment(const framebuffer_attachment& attachment)
    {
        _depth = attachment;
        _impl->set_color_attachment(_color);
    }

    const framebuffer_attachment& framebuffer::stencil_attachment() const
    {
        return _stencil;
    }

    void framebuffer::set_stencil_attachment(const framebuffer_attachment& attachment)
    {
        _stencil = attachment;
        _impl->set_color_attachment(_color);
    }

    GLenum framebuffer::preferred_read_format() const
    {
        return _impl->preferred_read_format();
    }

    GLenum framebuffer::preferred_read_type() const
    {
        return _impl->preferred_read_type();
    }

    void framebuffer::read_pixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* data)
    {
        _impl->read_pixels(x, y, width, height, format, type, data);
    }

    GLenum framebuffer::status() const
    {
        return _impl->status();
    }

    std::weak_ptr<framebuffer_impl> framebuffer::impl()
    {
        return _impl;
    }

    std::weak_ptr<const framebuffer_impl> framebuffer::impl() const
    {
        return _impl;
    }
}
