#ifndef _FIXIE_LIB_NULL_FRAMEBUFFER_HPP_
#define _FIXIE_LIB_NULL_FRAMEBUFFER_HPP_

#include "fixie_lib/framebuffer.hpp"

namespace fixie
{
    namespace null_impl
    {
        class framebuffer : public fixie::framebuffer_impl
        {
        public:
            virtual void set_color_attachment(const framebuffer_attachment& attachment) override;
            virtual void set_depth_attachment(const framebuffer_attachment& attachment) override;
            virtual void set_stencil_attachment(const framebuffer_attachment& attachment) override;

            virtual GLenum preferred_read_format() const override;
            virtual GLenum preferred_read_type() const override;
            virtual void read_pixels(const pixel_store_state& store_state, GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* data) override;

            virtual GLenum status() const override;
        };
    }
}

#endif // _FIXIE_LIB_NULL_FRAMEBUFFER_HPP_
