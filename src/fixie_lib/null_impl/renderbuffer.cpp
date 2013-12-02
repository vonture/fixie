#include "fixie_lib/null_impl/renderbuffer.hpp"

namespace fixie
{
    namespace null_impl
    {
        GLsizei renderbuffer::red_size() const
        {
            return 0;
        }

        GLsizei renderbuffer::green_size() const
        {
            return 0;
        }

        GLsizei renderbuffer::blue_size() const
        {
            return 0;
        }

        GLsizei renderbuffer::alpha_size() const
        {
            return 0;
        }

        GLsizei renderbuffer::depth_size() const
        {
            return 0;
        }

        GLsizei renderbuffer::stencil_size() const
        {
            return 0;
        }

        void renderbuffer::set_storage(GLenum target, GLenum internal_format, GLsizei width, GLsizei height)
        {
        }

        void renderbuffer::set_storage_multisample(GLenum target, GLsizei samples, GLenum internal_format, GLsizei width, GLsizei height)
        {
        }
    }
}
