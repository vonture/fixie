#include "fixie_lib/desktop_gl_impl/framebuffer.hpp"
#include "fixie_lib/debug.hpp"

namespace fixie
{
    namespace desktop_gl_impl
    {
        framebuffer::framebuffer(std::shared_ptr<const gl_functions> functions)
        {
        }

        framebuffer::~framebuffer()
        {
        }

        GLuint framebuffer::id() const
        {
            UNIMPLEMENTED();
            return 0;
        }

        void framebuffer::set_color_attachment(const framebuffer_attachment& attachment)
        {
            UNIMPLEMENTED();
        }

        void framebuffer::set_depth_attachment(const framebuffer_attachment& attachment)
        {
            UNIMPLEMENTED();
        }

        void framebuffer::set_stencil_attachment(const framebuffer_attachment& attachment)
        {
            UNIMPLEMENTED();
        }

        GLenum framebuffer::preferred_read_format() const 
        {
            UNIMPLEMENTED();
            return 0;
        }

        GLenum framebuffer::preferred_read_type() const 
        {
            UNIMPLEMENTED();
            return 0;
        }

        void framebuffer::read_pixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* data)
        {
            UNIMPLEMENTED();
        }

        GLenum framebuffer::status() const 
        {
            UNIMPLEMENTED();
            return 0;
        }
    }
}
