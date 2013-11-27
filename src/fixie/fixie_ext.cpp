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

void FIXIE_APIENTRY glDebugMessageControlKHR(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glDebugMessageInsertKHR(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *buf)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glDebugMessageCallbackKHR(GLDEBUGPROCKHR callback, const void *userParam)
{
    UNIMPLEMENTED();
}

GLuint FIXIE_APIENTRY glGetDebugMessageLogKHR(GLuint count, GLsizei bufsize, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *messageLog)
{
    UNIMPLEMENTED();
    return 0;
}

void FIXIE_APIENTRY glPushDebugGroupKHR(GLenum source, GLuint id, GLsizei length, const GLchar *message)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glPopDebugGroupKHR(void)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glObjectLabelKHR(GLenum identifier, GLuint name, GLsizei length, const GLchar *label)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glGetObjectLabeKHRl(GLenum identifier, GLuint name, GLsizei bufSize, GLsizei *length, GLchar *label)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glObjectPtrLabelKHR(const void *ptr, GLsizei length, const GLchar *label)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glGetObjectPtrLabelKHR(const void *ptr, GLsizei bufSize, GLsizei *length, GLchar *label)
{
    UNIMPLEMENTED();
}

}
