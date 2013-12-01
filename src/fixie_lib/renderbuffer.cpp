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
