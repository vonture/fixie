#include <stddef.h>
#include <vector>
#include <set>
#include <algorithm>

#include "fixie/fixie.h"
#include "fixie/fixie_ext.h"
#include "fixie/fixie_gl_es.h"
#include "fixie/fixie_gl_es_ext.h"

#include "fixie_lib/debug.hpp"
#include "fixie_lib/context.hpp"
#include "fixie_lib/exceptions.hpp"
#include "fixie_lib/util.hpp"
#include "fixie_lib/math_util.hpp"
#include "fixie_lib/enum_names.hpp"

extern "C"
{

GLboolean FIXIE_APIENTRY glIsRenderbufferOES(GLuint renderbuffer)
{
    try
    {
        std::shared_ptr<fixie::context> ctx = fixie::get_current_context();

        if (!ctx->caps().supports_framebuffer_objects())
        {
            throw fixie::invalid_operation_error("renderbuffers are not supported.");
        }

        return (ctx->state().renderbuffer(renderbuffer).use_count() > 0) ? GL_TRUE : GL_FALSE;
    }
    catch (const fixie::gl_error& e)
    {
        fixie::log_gl_error(e);
        return GL_FALSE;
    }
    catch (const fixie::context_error& e)
    {
        fixie::log_context_error(e);
        return GL_FALSE;
    }
    catch (...)
    {
        UNREACHABLE();
        return GL_FALSE;
    }
}

void FIXIE_APIENTRY glBindRenderbufferOES(GLenum target, GLuint renderbuffer)
{
    try
    {
        std::shared_ptr<fixie::context> ctx = fixie::get_current_context();

        if (!ctx->caps().supports_framebuffer_objects())
        {
            throw fixie::invalid_operation_error("renderbuffers are not supported.");
        }

        std::weak_ptr<fixie::renderbuffer> rb = ctx->state().renderbuffer(renderbuffer);

        switch (target)
        {
        case GL_RENDERBUFFER_OES:
            ctx->state().bind_renderbuffer(rb);
            break;

        default:
            throw fixie::invalid_enum_error(fixie::format("unknown renderbuffer binding target, %s.", fixie::get_gl_enum_name(target).c_str()));
        }
    }
    catch (const fixie::gl_error& e)
    {
        fixie::log_gl_error(e);
    }
    catch (const fixie::context_error& e)
    {
        fixie::log_context_error(e);
    }
    catch (...)
    {
        UNREACHABLE();
    }
}

void FIXIE_APIENTRY glDeleteRenderbuffersOES(GLsizei n, const GLuint* renderbuffers)
{
    try
    {
        std::shared_ptr<fixie::context> ctx = fixie::get_current_context();

        if (!ctx->caps().supports_framebuffer_objects())
        {
            throw fixie::invalid_operation_error("renderbuffers are not supported.");
        }

        if (n < 0)
        {
            throw fixie::invalid_value_error(fixie::format("invalid number of renderbuffers, at least 0 required, %i provided.", n));
        }

        fixie::for_each_n(0, n, [&](size_t i){ ctx->state().delete_renderbuffer(renderbuffers[i]); });
    }
    catch (const fixie::gl_error& e)
    {
        fixie::log_gl_error(e);
    }
    catch (const fixie::context_error& e)
    {
        fixie::log_context_error(e);
    }
    catch (...)
    {
        UNREACHABLE();
    }
}

void FIXIE_APIENTRY glGenRenderbuffersOES(GLsizei n, GLuint* renderbuffers)
{
    try
    {
        std::shared_ptr<fixie::context> ctx = fixie::get_current_context();

        if (!ctx->caps().supports_framebuffer_objects())
        {
            throw fixie::invalid_operation_error("renderbuffers are not supported.");
        }

        if (n < 0)
        {
            throw fixie::invalid_value_error(fixie::format("invalid number of renderbuffers, at least 0 required, %i provided.", n));
        }

        std::fill(renderbuffers, renderbuffers + n, 0);

        try
        {
            std::generate_n(renderbuffers, n, [&](){ return ctx->create_renderbuffer(); });
        }
        catch (...)
        {
            try
            {
                std::for_each(renderbuffers, renderbuffers + n, [&](GLuint rb){ ctx->state().delete_renderbuffer(rb); });
            }
            catch (...)
            {
                // error while deleting a renderbuffer, ignore it
            }

            throw;
        }
    }
    catch (const fixie::gl_error& e)
    {
        fixie::log_gl_error(e);
    }
    catch (const fixie::context_error& e)
    {
        fixie::log_context_error(e);
    }
    catch (...)
    {
        UNREACHABLE();
    }
}

void FIXIE_APIENTRY glRenderbufferStorageOES(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
{
    try
    {
        std::shared_ptr<fixie::context> ctx = fixie::get_current_context();

        if (!ctx->caps().supports_framebuffer_objects())
        {
            throw fixie::invalid_operation_error("renderbuffers are not supported.");
        }

        if (target != GL_RENDERBUFFER_OES)
        {
            throw fixie::invalid_enum_error(fixie::format("renderbuffer target must be GL_RENDERBUFFER_OES, %s provided.", fixie::get_gl_enum_name(target).c_str()));
        }

        std::set<GLenum> valid_internal_formats;
        valid_internal_formats.insert(GL_RGB565_OES);
        valid_internal_formats.insert(GL_RGBA4_OES);
        valid_internal_formats.insert(GL_RGB5_A1_OES);
        valid_internal_formats.insert(GL_DEPTH_COMPONENT16_OES);
        if (ctx->caps().supports_rgb8_rgba8())
        {
            valid_internal_formats.insert(GL_RGBA8_OES);
            valid_internal_formats.insert(GL_RGB8_OES);
        }
        if (ctx->caps().supports_depth24())
        {
            valid_internal_formats.insert(GL_DEPTH_COMPONENT24_OES);
        }
        if (ctx->caps().supports_depth32())
        {
            valid_internal_formats.insert(GL_DEPTH_COMPONENT32_OES);
        }
        if (ctx->caps().supports_stencil1())
        {
            valid_internal_formats.insert(GL_DEPTH_COMPONENT32_OES);
        }
        if (ctx->caps().supports_stencil4())
        {
            valid_internal_formats.insert(GL_STENCIL_INDEX4_OES);
        }
        if (ctx->caps().supports_stencil8())
        {
            valid_internal_formats.insert(GL_STENCIL_INDEX8_OES);
        }

        if (valid_internal_formats.find(internalformat) == valid_internal_formats.end())
        {
            throw fixie::invalid_value_error(fixie::format("invalid internal format, %s", fixie::get_gl_enum_name(internalformat).c_str()));
        }

        std::shared_ptr<fixie::renderbuffer> renderbuffer = ctx->state().bound_renderbuffer().lock();
        if (renderbuffer != nullptr)
        {
            renderbuffer->set_storage(target, internalformat, width, height);
        }
    }
    catch (const fixie::gl_error& e)
    {
        fixie::log_gl_error(e);
    }
    catch (const fixie::context_error& e)
    {
        fixie::log_context_error(e);
    }
    catch (...)
    {
        UNREACHABLE();
    }
}

void FIXIE_APIENTRY glGetRenderbufferParameterivOES(GLenum target, GLenum pname, GLint* params)
{
    try
    {
        std::shared_ptr<fixie::context> ctx = fixie::get_current_context();

        if (!ctx->caps().supports_framebuffer_objects())
        {
            throw fixie::invalid_operation_error("renderbuffers are not supported.");
        }

        if (target != GL_RENDERBUFFER_OES)
        {
            throw fixie::invalid_enum_error(fixie::format("renderbuffer target must be GL_RENDERBUFFER_OES, %s provided.", fixie::get_gl_enum_name(target).c_str()));
        }

        std::shared_ptr<fixie::renderbuffer> renderbuffer = ctx->state().bound_renderbuffer().lock();

        switch (pname)
        {
        case GL_RENDERBUFFER_WIDTH_OES:
            if (renderbuffer != nullptr)
            {
                *params = renderbuffer->width();
            }
            break;

        case GL_RENDERBUFFER_HEIGHT_OES:
            if (renderbuffer != nullptr)
            {
                *params = renderbuffer->height();
            }
            break;

        case GL_RENDERBUFFER_INTERNAL_FORMAT_OES:
            if (renderbuffer != nullptr)
            {
                *params = renderbuffer->internal_format();
            }
            break;

        case GL_RENDERBUFFER_RED_SIZE_OES:
            if (renderbuffer != nullptr)
            {
                *params = renderbuffer->red_size();
            }
            break;

        case GL_RENDERBUFFER_GREEN_SIZE_OES:
            if (renderbuffer != nullptr)
            {
                *params = renderbuffer->green_size();
            }
            break;

        case GL_RENDERBUFFER_BLUE_SIZE_OES:
            if (renderbuffer != nullptr)
            {
                *params = renderbuffer->blue_size();
            }
            break;

        case GL_RENDERBUFFER_ALPHA_SIZE_OES:
            if (renderbuffer != nullptr)
            {
                *params = renderbuffer->alpha_size();
            }
            break;

        case GL_RENDERBUFFER_DEPTH_SIZE_OES:
            if (renderbuffer != nullptr)
            {
                *params = renderbuffer->depth_size();
            }
            break;

        case GL_RENDERBUFFER_STENCIL_SIZE_OES:
            if (renderbuffer != nullptr)
            {
                *params = renderbuffer->stencil_size();
            }
            break;

        default:
            throw fixie::invalid_enum_error(fixie::format("invalid renderbuffer parameter name, %s.", fixie::get_gl_enum_name(pname).c_str()));
        }
    }
    catch (const fixie::gl_error& e)
    {
        fixie::log_gl_error(e);
    }
    catch (const fixie::context_error& e)
    {
        fixie::log_context_error(e);
    }
    catch (...)
    {
        UNREACHABLE();
    }
}

GLboolean FIXIE_APIENTRY glIsFramebufferOES(GLuint framebuffer)
{
    try
    {
        std::shared_ptr<fixie::context> ctx = fixie::get_current_context();

        if (!ctx->caps().supports_framebuffer_objects())
        {
            throw fixie::invalid_operation_error("framebuffers are not supported.");
        }

        return (ctx->state().framebuffer(framebuffer).use_count() > 0) ? GL_TRUE : GL_FALSE;
    }
    catch (const fixie::gl_error& e)
    {
        fixie::log_gl_error(e);
        return GL_FALSE;
    }
    catch (const fixie::context_error& e)
    {
        fixie::log_context_error(e);
        return GL_FALSE;
    }
    catch (...)
    {
        UNREACHABLE();
        return GL_FALSE;
    }
}

void FIXIE_APIENTRY glBindFramebufferOES(GLenum target, GLuint framebuffer)
{
    try
    {
        std::shared_ptr<fixie::context> ctx = fixie::get_current_context();

        if (!ctx->caps().supports_framebuffer_objects())
        {
            throw fixie::invalid_operation_error("framebuffers are not supported.");
        }

        std::weak_ptr<fixie::framebuffer> fbo = ctx->state().framebuffer(framebuffer);

        switch (target)
        {
        case GL_FRAMEBUFFER_OES:
            ctx->state().bind_framebuffer(fbo);
            break;

        default:
            throw fixie::invalid_enum_error(fixie::format("unknown framebuffer target, %s.", fixie::get_gl_enum_name(target).c_str()));
        }
    }
    catch (const fixie::gl_error& e)
    {
        fixie::log_gl_error(e);
    }
    catch (const fixie::context_error& e)
    {
        fixie::log_context_error(e);
    }
    catch (...)
    {
        UNREACHABLE();
    }
}

void FIXIE_APIENTRY glDeleteFramebuffersOES(GLsizei n, const GLuint* framebuffers)
{
    try
    {
        std::shared_ptr<fixie::context> ctx = fixie::get_current_context();

        if (!ctx->caps().supports_framebuffer_objects())
        {
            throw fixie::invalid_operation_error("framebuffers are not supported.");
        }

        if (n < 0)
        {
            throw fixie::invalid_value_error(fixie::format("invalid number of framebuffers, at least 0 required, %i provided.", n));
        }

        fixie::for_each_n(0, n, [&](size_t i){ ctx->state().delete_framebuffer(framebuffers[i]); });
    }
    catch (const fixie::gl_error& e)
    {
        fixie::log_gl_error(e);
    }
    catch (const fixie::context_error& e)
    {
        fixie::log_context_error(e);
    }
    catch (...)
    {
        UNREACHABLE();
    }
}

void FIXIE_APIENTRY glGenFramebuffersOES(GLsizei n, GLuint* framebuffers)
{
    try
    {
        std::shared_ptr<fixie::context> ctx = fixie::get_current_context();

        if (!ctx->caps().supports_framebuffer_objects())
        {
            throw fixie::invalid_operation_error("framebuffers are not supported.");
        }

        if (n < 0)
        {
            throw fixie::invalid_value_error(fixie::format("invalid number of framebuffers, at least 0 required, %i provided.", n));
        }

        std::fill(framebuffers, framebuffers + n, 0);

        try
        {
            std::generate_n(framebuffers, n, [&](){ return ctx->create_framebuffer(); });
        }
        catch (...)
        {
            try
            {
                std::for_each(framebuffers, framebuffers + n, [&](GLuint fbo){ ctx->state().delete_framebuffer(fbo); });
            }
            catch (...)
            {
                // error while deleting a framebuffer, ignore it
            }

            throw;
        }
    }
    catch (const fixie::gl_error& e)
    {
        fixie::log_gl_error(e);
    }
    catch (const fixie::context_error& e)
    {
        fixie::log_context_error(e);
    }
    catch (...)
    {
        UNREACHABLE();
    }
}

GLenum FIXIE_APIENTRY glCheckFramebufferStatusOES(GLenum target)
{
    try
    {
        std::shared_ptr<fixie::context> ctx = fixie::get_current_context();

        if (!ctx->caps().supports_framebuffer_objects())
        {
            throw fixie::invalid_operation_error("framebuffers are not supported.");
        }

        std::shared_ptr<fixie::framebuffer> framebuffer;

        switch (target)
        {
        case GL_FRAMEBUFFER_OES:
            framebuffer = ctx->state().bound_framebuffer().lock();
            break;

        default:
            throw fixie::invalid_enum_error(fixie::format("unknown framebuffer target, %s.", fixie::get_gl_enum_name(target).c_str()));
        }

        if (framebuffer == nullptr)
        {
            throw fixie::state_error("null framebuffer bound.");
        }

        return framebuffer->status();
    }
    catch (const fixie::gl_error& e)
    {
        fixie::log_gl_error(e);
        return 0;
    }
    catch (const fixie::context_error& e)
    {
        fixie::log_context_error(e);
        return 0;
    }
    catch (...)
    {
        UNREACHABLE();
        return 0;
    }
}

void FIXIE_APIENTRY glFramebufferRenderbufferOES(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
{
    try
    {
        std::shared_ptr<fixie::context> ctx = fixie::get_current_context();

        if (!ctx->caps().supports_framebuffer_objects())
        {
            throw fixie::invalid_operation_error("framebuffers are not supported.");
        }

        std::shared_ptr<fixie::framebuffer> framebuffer;
        switch (target)
        {
        case GL_FRAMEBUFFER_OES:
            framebuffer = ctx->state().bound_framebuffer().lock();
            break;

        default:
            throw fixie::invalid_enum_error(fixie::format("unknown framebuffer target, %s.", fixie::get_gl_enum_name(target).c_str()));
        }

        if (framebuffer == nullptr)
        {
            throw fixie::state_error("null framebuffer bound.");
        }

        std::weak_ptr<fixie::renderbuffer> rb;
        switch (renderbuffertarget)
        {
        case GL_RENDERBUFFER_OES:
            rb = ctx->state().renderbuffer(renderbuffer);
            break;

        default:
            throw fixie::invalid_enum_error(fixie::format("unknown renderbuffer target, %s.", fixie::get_gl_enum_name(renderbuffertarget).c_str()));
        }

        fixie::framebuffer_attachment attach(rb);
        switch (attachment)
        {
        case GL_COLOR_ATTACHMENT0_OES:
            framebuffer->set_color_attachment(attach);
            break;

        case GL_DEPTH_ATTACHMENT_OES:
            framebuffer->set_depth_attachment(attach);
            break;

        case GL_STENCIL_ATTACHMENT_OES:
            framebuffer->set_stencil_attachment(attach);
            break;

        default:
            throw fixie::invalid_enum_error(fixie::format("unknown framebuffer attachment, %s.", fixie::get_gl_enum_name(attachment).c_str()));
        }
    }
    catch (const fixie::gl_error& e)
    {
        fixie::log_gl_error(e);
    }
    catch (const fixie::context_error& e)
    {
        fixie::log_context_error(e);
    }
    catch (...)
    {
        UNREACHABLE();
    }
}

void FIXIE_APIENTRY glFramebufferTexture2DOES(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
    try
    {
        std::shared_ptr<fixie::context> ctx = fixie::get_current_context();

        if (!ctx->caps().supports_framebuffer_objects())
        {
            throw fixie::invalid_operation_error("framebuffers are not supported.");
        }

        std::shared_ptr<fixie::framebuffer> framebuffer;
        switch (target)
        {
        case GL_FRAMEBUFFER_OES:
            framebuffer = ctx->state().bound_framebuffer().lock();
            break;

        default:
            throw fixie::invalid_enum_error(fixie::format("unknown framebuffer target, %s.", fixie::get_gl_enum_name(target).c_str()));
        }

        if (framebuffer == nullptr)
        {
            throw fixie::state_error("null framebuffer bound.");
        }

        std::weak_ptr<fixie::texture> tex;
        switch (textarget)
        {
        case GL_TEXTURE_2D:
            tex = ctx->state().texture(texture);
            break;

        default:
            throw fixie::invalid_enum_error(fixie::format("unknown texture target, %s.", fixie::get_gl_enum_name(textarget).c_str()));
        }

        fixie::framebuffer_attachment attach(tex, level, 1);
        switch (attachment)
        {
        case GL_COLOR_ATTACHMENT0_OES:
            framebuffer->set_color_attachment(attach);
            break;

        case GL_DEPTH_ATTACHMENT_OES:
            framebuffer->set_depth_attachment(attach);
            break;

        case GL_STENCIL_ATTACHMENT_OES:
            framebuffer->set_stencil_attachment(attach);
            break;

        default:
            throw fixie::invalid_enum_error(fixie::format("unknown framebuffer attachment, %s.", fixie::get_gl_enum_name(attachment).c_str()));
        }
    }
    catch (const fixie::gl_error& e)
    {
        fixie::log_gl_error(e);
    }
    catch (const fixie::context_error& e)
    {
        fixie::log_context_error(e);
    }
    catch (...)
    {
        UNREACHABLE();
    }
}

void FIXIE_APIENTRY glGetFramebufferAttachmentParameterivOES(GLenum target, GLenum attachment, GLenum pname, GLint* params)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glGenerateMipmapOES(GLenum target)
{
    try
    {
        std::shared_ptr<fixie::context> ctx = fixie::get_current_context();

        std::shared_ptr<fixie::texture> tex;
        switch (target)
        {
        case GL_TEXTURE_2D:
            tex = ctx->state().bound_texture(ctx->state().active_texture_unit()).lock();
            break;

        default:
            throw fixie::invalid_enum_error(fixie::format("unknown texture target, %s.", fixie::get_gl_enum_name(target).c_str()));
        }

        if (tex != nullptr)
        {
            if (!fixie::is_power_of_two(tex->mip_level_width(0)) || !fixie::is_power_of_two(tex->mip_level_height(0)))
            {
                throw fixie::invalid_operation_error(fixie::format("texture zero level array must be have a power of two width and height, "
                                                                   "width and height are %i and %i.", tex->mip_level_width(0), tex->mip_level_height(0)));
            }

            if (tex->mip_level_compressed(0))
            {
                throw fixie::invalid_operation_error("texture zero level array cannot be compressed.");
            }

            tex->generate_mipmaps();
        }
    }
    catch (const fixie::gl_error& e)
    {
        fixie::log_gl_error(e);
    }
    catch (const fixie::context_error& e)
    {
        fixie::log_context_error(e);
    }
    catch (...)
    {
        UNREACHABLE();
    }
}

void FIXIE_APIENTRY glBindVertexArrayOES(GLuint array)
{
    try
    {
        std::shared_ptr<fixie::context> ctx = fixie::get_current_context();

        if (!ctx->caps().supports_vertex_array_objects())
        {
            throw fixie::invalid_operation_error("vertex array objects are not supported.");
        }

        ctx->state().bind_vertex_array(ctx->state().vertex_array(array));
    }
    catch (const fixie::gl_error& e)
    {
        fixie::log_gl_error(e);
    }
    catch (const fixie::context_error& e)
    {
        fixie::log_context_error(e);
    }
    catch (...)
    {
        UNREACHABLE();
    }
}

void FIXIE_APIENTRY glDeleteVertexArraysOES(GLsizei n, const GLuint *arrays)
{
    try
    {
        std::shared_ptr<fixie::context> ctx = fixie::get_current_context();

        if (!ctx->caps().supports_vertex_array_objects())
        {
            throw fixie::invalid_operation_error("vertex array objects are not supported.");
        }

        if (n < 0)
        {
            throw fixie::invalid_value_error(fixie::format("invalid number of textures, at least 0 required, %i provided.", n));
        }

        std::for_each(arrays, arrays + n, [&](GLuint array){ if (array) { ctx->state().delete_vertex_array(array); } });
    }
    catch (const fixie::gl_error& e)
    {
        fixie::log_gl_error(e);
    }
    catch (const fixie::context_error& e)
    {
        fixie::log_context_error(e);
    }
    catch (...)
    {
        UNREACHABLE();
    }
}

void FIXIE_APIENTRY glGenVertexArraysOES(GLsizei n, GLuint *arrays)
{
    try
    {
        std::shared_ptr<fixie::context> ctx = fixie::get_current_context();

        if (!ctx->caps().supports_vertex_array_objects())
        {
            throw fixie::invalid_operation_error("vertex array objects are not supported.");
        }

        if (n < 0)
        {
            throw fixie::invalid_value_error(fixie::format("invalid number of textures, at least 0 required, %i provided.", n));
        }

        std::fill(arrays, arrays + n, 0);

        try
        {
            std::generate_n(arrays, n, [&](){ return ctx->create_vertex_array(); });
        }
        catch(...)
        {
            try
            {
                std::for_each(arrays, arrays + n, [&](GLuint array){ if (array) { ctx->state().delete_vertex_array(array); } });
            }
            catch (...)
            {
                // error while deleting a vertex array, ignore it
            }

            throw;
        }
    }
    catch (const fixie::gl_error& e)
    {
        fixie::log_gl_error(e);
    }
    catch (const fixie::context_error& e)
    {
        fixie::log_context_error(e);
    }
    catch (...)
    {
        UNREACHABLE();
    }
}

GLboolean FIXIE_APIENTRY glIsVertexArrayOES(GLuint array)
{
    try
    {
        std::shared_ptr<fixie::context> ctx = fixie::get_current_context();

        if (!ctx->caps().supports_vertex_array_objects())
        {
            throw fixie::invalid_operation_error("vertex array objects are not supported.");
        }

        return (ctx->state().vertex_array(array).use_count() > 0) ? GL_TRUE : GL_FALSE;
    }
    catch (const fixie::gl_error& e)
    {
        fixie::log_gl_error(e);
        return GL_FALSE;
    }
    catch (const fixie::context_error& e)
    {
        fixie::log_context_error(e);
        return GL_FALSE;
    }
    catch (...)
    {
        UNREACHABLE();
        return GL_FALSE;
    }
}

}
