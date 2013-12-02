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
        virtual GLsizei red_size() const = 0;
        virtual GLsizei green_size() const = 0;
        virtual GLsizei blue_size() const = 0;
        virtual GLsizei alpha_size() const = 0;
        virtual GLsizei depth_size() const = 0;
        virtual GLsizei stencil_size() const = 0;

        virtual void set_storage(GLenum target, GLenum internal_format, GLsizei width, GLsizei height) = 0;
        virtual void set_storage_multisample(GLenum target, GLsizei samples, GLenum internal_format, GLsizei width, GLsizei height) = 0;
    };

    class renderbuffer : public noncopyable
    {
    public:
        explicit renderbuffer(std::unique_ptr<renderbuffer_impl> impl);

        GLsizei red_size() const;
        GLsizei green_size() const;
        GLsizei blue_size() const;
        GLsizei alpha_size() const;
        GLsizei depth_size() const;
        GLsizei stencil_size() const;

        GLsizei width() const;
        GLsizei height() const;

        GLenum internal_format() const;

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
