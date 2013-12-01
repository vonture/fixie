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
            virtual void set_storage(GLenum target, GLenum internal_format, GLsizei width, GLsizei height) override;
            virtual void set_storage_multisample(GLenum target, GLsizei samples, GLenum internal_format, GLsizei width, GLsizei height) override;
        };
    }
}

#endif // _NULL_RENDERBUFFER_HPP_
