#ifndef _RENDERBUFFER_HPP_
#define _RENDERBUFFER_HPP_

#include <memory>

#include "fixie/fixie_gl_types.h"
#include "fixie_lib/noncopyable.hpp"

namespace fixie
{
    class renderbuffer_impl : public noncopyable
    {
    public:
        virtual void set_storage(GLenum target, GLenum internal_format, GLsizei width, GLsizei height) = 0;
        virtual void set_storage_multisample(GLenum target, GLsizei samples, GLenum internal_format, GLsizei width, GLsizei height) = 0;
    };

    class renderbuffer : public noncopyable
    {
    public:
        explicit renderbuffer(std::unique_ptr<renderbuffer_impl> impl);

        void set_storage(GLenum target, GLenum internal_format, GLsizei width, GLsizei height);
        void set_storage_multisample(GLenum target, GLsizei samples, GLenum internal_format, GLsizei width, GLsizei height);

        std::weak_ptr<renderbuffer_impl> impl();
        std::weak_ptr<const renderbuffer_impl> impl() const;

    private:
        GLenum _internal_format;
        GLsizei _samples;
        GLsizei _width;
        GLsizei _height;

        std::shared_ptr<renderbuffer_impl> _impl;
    };
}

#endif // _RENDERBUFFER_HPP_
