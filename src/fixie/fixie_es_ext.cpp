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

}
