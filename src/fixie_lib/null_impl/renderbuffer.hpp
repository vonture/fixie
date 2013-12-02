#ifndef _NULL_RENDERBUFFER_HPP_
#define _NULL_RENDERBUFFER_HPP_

#include "fixie_lib/renderbuffer.hpp"

namespace fixie
{
    namespace null_impl
    {
        class renderbuffer : public fixie::renderbuffer_impl
        {
        public:
            virtual GLsizei red_size() const override;
            virtual GLsizei green_size() const override;
            virtual GLsizei blue_size() const override;
            virtual GLsizei alpha_size() const override;
            virtual GLsizei depth_size() const override;
            virtual GLsizei stencil_size() const override;

            virtual void set_storage(GLenum target, GLenum internal_format, GLsizei width, GLsizei height) override;
            virtual void set_storage_multisample(GLenum target, GLsizei samples, GLenum internal_format, GLsizei width, GLsizei height) override;
        };
    }
}

#endif // _NULL_RENDERBUFFER_HPP_
