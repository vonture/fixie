#include "fixie_lib/renderbuffer.hpp"

namespace fixie
{
    renderbuffer::renderbuffer(std::unique_ptr<renderbuffer_impl> impl)
        : _internal_format(0)
        , _samples(0)
        , _width(0)
        , _height(0)
        , _impl(std::move(impl))
    {
    }

    GLsizei renderbuffer::red_size() const
    {
        return _impl->red_size();
    }

    GLsizei renderbuffer::green_size() const
    {
        return _impl->green_size();
    }

    GLsizei renderbuffer::blue_size() const
    {
        return _impl->blue_size();
    }

    GLsizei renderbuffer::alpha_size() const
    {
        return _impl->alpha_size();
    }

    GLsizei renderbuffer::depth_size() const
    {
        return _impl->depth_size();
    }

    GLsizei renderbuffer::stencil_size() const
    {
        return _impl->stencil_size();
    }

    GLsizei renderbuffer::width() const
    {
        return _width;
    }

    GLsizei renderbuffer::height() const
    {
        return _height;
    }

    GLenum renderbuffer::internal_format() const
    {
        return _internal_format;
    }

    void renderbuffer::set_storage(GLenum target, GLenum internal_format, GLsizei width, GLsizei height)
    {
        _impl->set_storage(target, internal_format, width, height);

        _internal_format = internal_format;
        _samples = 1;
        _width = width;
        _height = height;
    }

    void renderbuffer::set_storage_multisample(GLenum target, GLsizei samples, GLenum internal_format, GLsizei width, GLsizei height)
    {
        _impl->set_storage_multisample(target, samples, internal_format, width, height);

        _internal_format = internal_format;
        _samples = samples;
        _width = width;
        _height = height;
    }

    std::weak_ptr<renderbuffer_impl> renderbuffer::impl()
    {
        return _impl;
    }

    std::weak_ptr<const renderbuffer_impl> renderbuffer::impl() const
    {
        return _impl;
    }
}
