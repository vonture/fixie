#include "buffer.hpp"

#include "fixie/fixie_gl_es.h"

namespace fixie
{
    buffer::buffer(std::unique_ptr<buffer_impl> impl)
        : _type(0)
        , _size(0)
        , _usage(GL_STATIC_DRAW)
        , _impl(std::move(impl))
    {
    }

    GLenum buffer::type() const
    {
        return _type;
    }

    GLsizei buffer::size() const
    {
        return _size;
    }

    GLenum buffer::usage() const
    {
        return _usage;
    }

    std::weak_ptr<buffer_impl> buffer::impl()
    {
        return _impl;
    }

    std::weak_ptr<const buffer_impl> buffer::impl() const
    {
        return _impl;
    }

    void buffer::bind(GLenum type)
    {
        if (_type != type)
        {
            _type = type;
            _impl->set_type(type);
        }
    }

    void buffer::set_data(GLsizeiptr size, const GLvoid* data, GLenum usage)
    {
        _impl->set_data(size, data, usage);
        _size = size;
        _usage = usage;
    }

    void buffer::set_sub_data(GLintptr offset, GLsizeiptr size, const GLvoid* data)
    {
        _impl->set_sub_data(offset, size, data);
    }
}
