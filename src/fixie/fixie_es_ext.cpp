#include <stddef.h>
#include <vector>
#include <set>

#include "fixie/fixie.h"
#include "fixie/fixie_ext.h"
#include "fixie/fixie_gl_es.h"
#include "fixie/fixie_gl_es_ext.h"

#include "fixie_lib/debug.hpp"
#include "fixie_lib/context.hpp"
#include "fixie_lib/exceptions.hpp"
#include "fixie_lib/util.hpp"

extern "C"
{

GLboolean FIXIE_APIENTRY glIsRenderbufferOES(GLuint renderbuffer)
{
    UNIMPLEMENTED();
    return GL_FALSE;
}

void FIXIE_APIENTRY glBindRenderbufferOES(GLenum target, GLuint renderbuffer)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glDeleteRenderbuffersOES(GLsizei n, const GLuint* renderbuffers)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glGenRenderbuffersOES(GLsizei n, GLuint* renderbuffers)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glRenderbufferStorageOES(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glGetRenderbufferParameterivOES(GLenum target, GLenum pname, GLint* params)
{
    UNIMPLEMENTED();
}

GLboolean FIXIE_APIENTRY glIsFramebufferOES(GLuint framebuffer)
{
    UNIMPLEMENTED();
    return GL_FALSE;
}

void FIXIE_APIENTRY glBindFramebufferOES(GLenum target, GLuint framebuffer)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glDeleteFramebuffersOES(GLsizei n, const GLuint* framebuffers)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glGenFramebuffersOES(GLsizei n, GLuint* framebuffers)
{
    UNIMPLEMENTED();
}

GLenum FIXIE_APIENTRY glCheckFramebufferStatusOES(GLenum target)
{
    UNIMPLEMENTED();
    return 0;
}

void FIXIE_APIENTRY glFramebufferRenderbufferOES(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glFramebufferTexture2DOES(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glGetFramebufferAttachmentParameterivOES(GLenum target, GLenum attachment, GLenum pname, GLint* params)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glGenerateMipmapOES(GLenum target)
{
    UNIMPLEMENTED();
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
