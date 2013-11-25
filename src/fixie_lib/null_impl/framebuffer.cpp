#include "fixie_lib/null_impl/framebuffer.hpp"

#include "fixie/fixie_gl_es.h"
#include "fixie/fixie_gl_es_ext.h"

namespace fixie
{
    namespace null_impl
    {
        void framebuffer::set_color_attachment(const framebuffer_attachment& attachment)
        {
        }

        void framebuffer::set_depth_attachment(const framebuffer_attachment& attachment)
        {
        }

        void framebuffer::set_stencil_attachment(const framebuffer_attachment& attachment)
        {
        }

        GLenum framebuffer::preferred_read_format() const 
        {
            return GL_RGBA;
        }

        GLenum framebuffer::preferred_read_type() const 
        {
            return GL_UNSIGNED_BYTE;
        }

        void framebuffer::read_pixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* data)
        {
        }

        GLenum framebuffer::status() const 
        {
            return GL_FRAMEBUFFER_COMPLETE_OES;
        }
    }
}
