#include "fixie_lib/desktop_gl_impl/framebuffer.hpp"
#include "fixie_lib/desktop_gl_impl/texture.hpp"
#include "fixie_lib/desktop_gl_impl/renderbuffer.hpp"
#include "fixie_lib/debug.hpp"

namespace fixie
{
    #define GL_FRAMEBUFFER 0x8D40
    #define GL_RENDERBUFFER 0x8D41
    #define GL_READ_FRAMEBUFFER 0x8CA8
    #define GL_DRAW_FRAMEBUFFER 0x8CA9
    #define GL_COLOR_ATTACHMENT0 0x8CE0
    #define GL_DEPTH_ATTACHMENT 0x8D00
    #define GL_STENCIL_ATTACHMENT 0x8D20

    #define GL_FRAMEBUFFER_COMPLETE 0x8CD5

    #define GL_IMPLEMENTATION_COLOR_READ_TYPE 0x8B9A
    #define GL_IMPLEMENTATION_COLOR_READ_FORMAT 0x8B9B

    namespace desktop_gl_impl
    {
        framebuffer::framebuffer(std::shared_ptr<const gl_functions> functions)
            : _functions(functions)
            , _id(0)
        {
            gl_call(_functions, gen_framebuffers, 1, &_id);
        }

        framebuffer::framebuffer(GLuint id, std::shared_ptr<const gl_functions> functions)
            : _functions(functions)
            , _id(id)
        {
        }

        framebuffer::~framebuffer()
        {
            if (_id)
            {
                gl_call_nothrow(_functions, delete_framebuffers, 1, &_id);
            }
        }

        GLuint framebuffer::id() const
        {
            return _id;
        }

        static void set_framebuffer_attachment(std::shared_ptr<const gl_functions> functions, GLuint framebuffer,
                                               GLenum attachment_point, const framebuffer_attachment& attachment)
        {
            if (framebuffer != 0)
            {
                gl_call(functions, bind_framebuffer, GL_FRAMEBUFFER, framebuffer);
                if (attachment.is_texture())
                {
                    std::shared_ptr<const fixie::texture> texture = attachment.texture().lock();
                    std::shared_ptr<const desktop_gl_impl::texture> texture_impl = texture ? std::dynamic_pointer_cast<const desktop_gl_impl::texture>(texture->impl().lock()) : nullptr;
                    GLuint id = texture_impl ? texture_impl->id() : 0;
                    if (attachment.texture_samples() > 1)
                    {
                        gl_call(functions, framebuffer_texture_2d, GL_FRAMEBUFFER, attachment_point, GL_TEXTURE_2D, id, attachment.texture_level());
                    }
                    else
                    {
                        gl_call(functions, framebuffer_texture_2d_multisample, GL_FRAMEBUFFER, attachment_point, GL_TEXTURE_2D, id, attachment.texture_level(), attachment.texture_samples());
                    }
                }
                else if (attachment.is_renderbuffer())
                {
                    std::shared_ptr<const fixie::renderbuffer> renderbuffer = attachment.renderbuffer().lock();
                    std::shared_ptr<const desktop_gl_impl::renderbuffer> renderbuffer_impl = renderbuffer ? std::dynamic_pointer_cast<const desktop_gl_impl::renderbuffer>(renderbuffer->impl().lock()) : nullptr;
                    GLuint id = renderbuffer_impl ? renderbuffer_impl->id() : 0;
                    gl_call(functions, framebuffer_renderbuffer, GL_FRAMEBUFFER, attachment_point, GL_RENDERBUFFER, id);
                }
                else
                {
                    assert(!attachment.is_bound());
                    gl_call(functions, framebuffer_texture_2d, GL_FRAMEBUFFER, attachment_point, GL_TEXTURE_2D, 0, 0);
                }
            }
        }

        void framebuffer::set_color_attachment(const framebuffer_attachment& attachment)
        {
            set_framebuffer_attachment(_functions, _id, GL_COLOR_ATTACHMENT0, attachment);
        }

        void framebuffer::set_depth_attachment(const framebuffer_attachment& attachment)
        {
            set_framebuffer_attachment(_functions, _id, GL_DEPTH_ATTACHMENT, attachment);
        }

        void framebuffer::set_stencil_attachment(const framebuffer_attachment& attachment)
        {
            set_framebuffer_attachment(_functions, _id, GL_STENCIL_ATTACHMENT, attachment);
        }

        GLenum framebuffer::preferred_read_format() const
        {
            gl_call(_functions, bind_framebuffer, GL_FRAMEBUFFER, _id);

            GLint read_format;
            gl_call(_functions, get_integer_v, GL_IMPLEMENTATION_COLOR_READ_FORMAT, &read_format);
            return static_cast<GLenum>(read_format);
        }

        GLenum framebuffer::preferred_read_type() const
        {
            gl_call(_functions, bind_framebuffer, GL_FRAMEBUFFER, _id);

            GLint read_type;
            gl_call(_functions, get_integer_v, GL_IMPLEMENTATION_COLOR_READ_TYPE, &read_type);
            return static_cast<GLenum>(read_type);
        }

        void framebuffer::read_pixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* data)
        {
            gl_call(_functions, bind_framebuffer, GL_FRAMEBUFFER, _id);
            gl_call(_functions, read_pixels, x, y, width, height, format, type, data);
        }

        GLenum framebuffer::status() const 
        {
            gl_call(_functions, bind_framebuffer, GL_FRAMEBUFFER, _id);
            GLenum status = gl_call(_functions, check_framebuffer_status, GL_FRAMEBUFFER);
            return status;
        }

        default_framebuffer::default_framebuffer(std::shared_ptr<const gl_functions> functions)
            : framebuffer(0, functions)
        {
        }

        GLenum default_framebuffer::status() const
        {
            return GL_FRAMEBUFFER_COMPLETE;
        }
    }
}
