#include "buffer.hpp"

#include "fixie_gl_es.h"

namespace fixie
{
    buffer::buffer(std::shared_ptr<buffer_impl> impl)
        : _size(0)
        , _usage(GL_STATIC_DRAW)
        , _impl(impl)
    {
    }

    GLsizei buffer::size() const
    {
        return _size;
    }

    GLenum buffer::usage() const
    {
        return _usage;
    }

    std::shared_ptr<buffer_impl> buffer::impl()
    {
        return _impl;
    }

    std::shared_ptr<const buffer_impl> buffer::impl() const
    {
        return _impl;
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
