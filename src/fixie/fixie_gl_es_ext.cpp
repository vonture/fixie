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

namespace fixie
{
    template <typename output_type>
    size_t get_framebuffer_attachment_parameter(GLenum target, GLenum attachment, GLenum pname, output_type* output)
    {
        try
        {
            std::shared_ptr<context> ctx = get_current_context();
            if (!ctx->caps().supports_framebuffer_objects())
            {
                throw invalid_operation_error("framebuffers are not supported.");
            }

            std::shared_ptr<framebuffer> framebuffer = ctx->state().bound_framebuffer().lock();

            const fixie::framebuffer_attachment* framebuffer_attachment = nullptr;
            switch (attachment)
            {
            case GL_COLOR_ATTACHMENT0_OES:
                framebuffer_attachment = &framebuffer->color_attachment();
                break;

            case GL_DEPTH_ATTACHMENT_OES:
                framebuffer_attachment = &framebuffer->depth_attachment();
                break;

            case GL_STENCIL_ATTACHMENT_OES:
                framebuffer_attachment = &framebuffer->stencil_attachment();
                break;

            default:
                throw invalid_enum_error(format("invalid framebuffer attachment, %s.", get_gl_enum_name(attachment).c_str()));
            }

            switch (pname)
            {
            case GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE_OES:
                if (!framebuffer_attachment->is_bound())
                {
                    output[0] = static_cast<output_type>(GL_NONE_OES);
                }
                else if (framebuffer_attachment->is_texture())
                {
                    output[0] = static_cast<output_type>(GL_TEXTURE);
                }
                else if (framebuffer_attachment->is_renderbuffer())
                {
                    output[0] = static_cast<output_type>(GL_RENDERBUFFER_OES);
                }
                else
                {
                    UNREACHABLE();
                }
                return 1;

            case GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME_OES:
                if (!framebuffer_attachment->is_bound())
                {
                    output[0] = static_cast<output_type>(0);
                }
                if (framebuffer_attachment->is_texture())
                {
                    output[0] = static_cast<output_type>(ctx->textures().get_handle(framebuffer_attachment->texture()));
                }
                else if (framebuffer_attachment->is_renderbuffer())
                {
                    output[0] = static_cast<output_type>(ctx->renderbuffers().get_handle(framebuffer_attachment->renderbuffer()));
                }
                else
                {
                    UNREACHABLE();
                }
                return 1;

            case GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL_OES:
                if (framebuffer_attachment->is_texture())
                {
                    output[0] = static_cast<output_type>(framebuffer_attachment->texture_level());
                }
                else
                {
                    throw invalid_operation_error("GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL_OES is not a valid query when a texture is not bound.");
                }
                return 1;

            case GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE_OES:
                if (framebuffer_attachment->is_texture())
                {
                    throw invalid_operation_error("cube maps are not supported.");
                }
                else
                {
                    throw invalid_operation_error("GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE_OES is not a valid query when a texture is not bound.");
                }
                return 1;

            default:
                throw invalid_enum_error(format("invalid framebuffer attachment parameter name, %s.", get_gl_enum_name(pname).c_str()));
            }
        }
        catch (gl_error e)
        {
            log_gl_error(e);
            return 0;
        }
        catch (context_error e)
        {
            log_context_error(e);
            return 0;
        }
        catch (...)
        {
            UNREACHABLE();
            return 0;
        }
    }

    template <typename output_type>
    size_t get_renderbuffer_parameter(GLenum target, GLenum pname, output_type* output)
    {
        try
        {
            std::shared_ptr<context> ctx = get_current_context();
            if (!ctx->caps().supports_framebuffer_objects())
            {
                throw invalid_operation_error("renderbuffers are not supported.");
            }

            std::shared_ptr<renderbuffer> renderbuffer;
            switch (target)
            {
            case GL_RENDERBUFFER_OES:
                renderbuffer = ctx->state().bound_renderbuffer().lock();
                break;

            default:
                throw invalid_enum_error(format("unknown renderbuffer target, %s.", get_gl_enum_name(target).c_str()));;
            }

            switch (pname)
            {
            case GL_RENDERBUFFER_WIDTH_OES:
                if (output != nullptr && renderbuffer != nullptr)
                {
                    output[0] = static_cast<output_type>(renderbuffer->width());
                }
                return 1;

            case GL_RENDERBUFFER_HEIGHT_OES:
                if (output != nullptr && renderbuffer != nullptr)
                {
                    output[0] = static_cast<output_type>(renderbuffer->height());
                }
                return 1;

            case GL_RENDERBUFFER_INTERNAL_FORMAT_OES:
                if (output != nullptr && renderbuffer != nullptr)
                {
                    output[0] = static_cast<output_type>(renderbuffer->internal_format());
                }
                return 1;

            case GL_RENDERBUFFER_RED_SIZE_OES:
                if (output != nullptr && renderbuffer != nullptr)
                {
                    output[0] = static_cast<output_type>(renderbuffer->red_size());
                }
                break;

            case GL_RENDERBUFFER_GREEN_SIZE_OES:
                if (output != nullptr && renderbuffer != nullptr)
                {
                    output[0] = static_cast<output_type>(renderbuffer->green_size());
                }
                return 1;

            case GL_RENDERBUFFER_BLUE_SIZE_OES:
                if (output != nullptr && renderbuffer != nullptr)
                {
                    output[0] = static_cast<output_type>(renderbuffer->blue_size());
                }
                return 1;

            case GL_RENDERBUFFER_ALPHA_SIZE_OES:
                if (output != nullptr && renderbuffer != nullptr)
                {
                    output[0] = static_cast<output_type>(renderbuffer->alpha_size());
                }
                return 1;

            case GL_RENDERBUFFER_DEPTH_SIZE_OES:
                if (output != nullptr && renderbuffer != nullptr)
                {
                    output[0] = static_cast<output_type>(renderbuffer->depth_size());
                }
                return 1;

            case GL_RENDERBUFFER_STENCIL_SIZE_OES:
                if (output != nullptr && renderbuffer != nullptr)
                {
                    output[0] = static_cast<output_type>(renderbuffer->stencil_size());
                }
                return 1;

            default:
                throw invalid_enum_error(format("invalid renderbuffer parameter name, %s.", get_gl_enum_name(pname).c_str()));
            }
        }
        catch (gl_error e)
        {
            log_gl_error(e);
            return 0;
        }
        catch (context_error e)
        {
            log_context_error(e);
            return 0;
        }
        catch (...)
        {
            UNREACHABLE();
            return 0;
        }
    }
}

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

        return ctx->renderbuffers().contains_handle(renderbuffer) ? GL_TRUE : GL_FALSE;
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

        std::weak_ptr<fixie::renderbuffer> rb = ctx->renderbuffers().get_object(renderbuffer);

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

        fixie::for_each_n(0, n, [&](size_t i){ ctx->renderbuffers().erase_object(renderbuffers[i]); });
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
                std::for_each(renderbuffers, renderbuffers + n, [&](GLuint rb){ ctx->renderbuffers().erase_object(rb); });
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
    fixie::get_renderbuffer_parameter(target, pname, params);
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

        return ctx->framebuffers().contains_handle(framebuffer) ? GL_TRUE : GL_FALSE;
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

        std::weak_ptr<fixie::framebuffer> fbo = ctx->framebuffers().get_object(framebuffer);

        // TODO: handle creating temporary framebuffers if fbo is null

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

        auto erase_func = [&](GLuint framebuffer)
        {
            std::shared_ptr<fixie::framebuffer> frammebuffer_object = ctx->framebuffers().get_object(framebuffer).lock();
            if (ctx->state().bound_framebuffer().lock() == frammebuffer_object)
            {
                ctx->state().bind_framebuffer(ctx->framebuffers().get_object(0));
            }

            ctx->framebuffers().erase_object(framebuffer);
        };

        std::for_each(framebuffers, framebuffers + n, erase_func);
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
                std::for_each(framebuffers, framebuffers + n, [&](GLuint fbo){ ctx->framebuffers().erase_object(fbo); });
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
            rb = ctx->renderbuffers().get_object(renderbuffer);
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
            tex = ctx->textures().get_object(texture);
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
    fixie::get_framebuffer_attachment_parameter(target, attachment, pname, params);
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

        std::weak_ptr<fixie::vertex_array> vao = ctx->vertex_arrays().get_object(array);
        if (vao.expired())
        {
            throw fixie::invalid_operation_error(fixie::format("vertex array %u is not valid.", array));
        }

        ctx->state().bind_vertex_array(vao);
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

        std::for_each(arrays, arrays + n, [&](GLuint array){ if (array) { ctx->vertex_arrays().erase_object(array); } });
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
                std::for_each(arrays, arrays + n, [&](GLuint array){ if (array) { ctx->vertex_arrays().erase_object(array); } });
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

        return ctx->vertex_arrays().contains_handle(array) ? GL_TRUE : GL_FALSE;
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
