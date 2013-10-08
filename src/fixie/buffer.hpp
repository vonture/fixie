#ifndef _BUFFER_HPP_
#define _BUFFER_HPP_

#include <memory>

#include "fixie/fixie_gl_types.h"
#include "fixie/noncopyable.hpp"

namespace fixie
{
    class buffer_impl : public noncopyable
    {
    public:
        virtual void set_type(GLenum type) = 0;
        virtual void set_data(GLsizeiptr size, const GLvoid* data, GLenum usage) = 0;
        virtual void set_sub_data(GLintptr offset, GLsizeiptr size, const GLvoid* data) = 0;
    };

    class buffer : public noncopyable
    {
    public:
        explicit buffer(std::shared_ptr<buffer_impl> impl);

        GLenum type() const;
        GLsizei size() const;
        GLenum usage() const;

        std::shared_ptr<buffer_impl> impl();
        std::shared_ptr<const buffer_impl> impl() const;

        void bind(GLenum type);
        void set_data(GLsizeiptr size, const GLvoid* data, GLenum usage);
        void set_sub_data(GLintptr offset, GLsizeiptr size, const GLvoid* data);

    private:
        GLenum _type;
        GLsizei _size;
        GLenum _usage;
        std::shared_ptr<buffer_impl> _impl;
    };
}

#endif // _BUFFER_HPP
