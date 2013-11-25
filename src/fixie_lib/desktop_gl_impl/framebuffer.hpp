#ifndef _DESKTOP_GL_FRAMEBUFFER_HPP_
#define _DESKTOP_GL_FRAMEBUFFER_HPP_

#include "fixie_lib/framebuffer.hpp"
#include "fixie_lib/desktop_gl_impl/gl_functions.hpp"

namespace fixie
{
    namespace desktop_gl_impl
    {
        class framebuffer : public fixie::framebuffer_impl
        {
        public:
            explicit framebuffer(std::shared_ptr<const gl_functions> functions);
            virtual ~framebuffer();

            GLuint id() const;

            virtual void set_color_attachment(const framebuffer_attachment& attachment) override;
            virtual void set_depth_attachment(const framebuffer_attachment& attachment) override;
            virtual void set_stencil_attachment(const framebuffer_attachment& attachment) override;

            virtual GLenum preferred_read_format() const override;
            virtual GLenum preferred_read_type() const override;
            virtual void read_pixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* data) override;

            virtual GLenum status() const override;

        private:
            std::shared_ptr<const gl_functions> _functions;
            GLuint _id;
        };
    }
}

#endif // _DESKTOP_GL_FRAMEBUFFER_HPP_
