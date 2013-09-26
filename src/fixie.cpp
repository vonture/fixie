#include <stddef.h>
#include <set>
#include <memory>
#include <algorithm>
#include <functional>

#include "fixie.h"
#include "fixie_gl_es.h"
#include "fixie_gl_es_ext.h"

#include "debug.hpp"
#include "context.hpp"
#include "exceptions.hpp"

namespace fixie
{
    std::shared_ptr<context> current_context;
    std::set< std::shared_ptr<context> > all_contexts;

    static std::shared_ptr<context> create_context()
    {
        std::shared_ptr<context> ctx(new context());
        all_contexts.insert(ctx);
        return ctx;
    }

    static bool context_equals(context* a, std::shared_ptr<context> b)
    {
        return a == b.get();
    }

    static void destroy_context(context* ctx)
    {
        if (ctx == current_context.get())
        {
            current_context = nullptr;
        }

        auto iter = std::find_if(all_contexts.begin(), all_contexts.end(), std::bind(context_equals, ctx, std::placeholders::_1));
        if (iter != all_contexts.end())
        {
            all_contexts.erase(iter);
        }
    }

    static std::shared_ptr<context> get_current_context()
    {
        if (!current_context && all_contexts.size() == 0)
        {
            current_context = create_context();
        }

        if (!current_context)
        {
            throw no_context_error();
        }

        return current_context;
    }

    static void set_current_context(context* ctx)
    {
        auto iter = std::find_if(all_contexts.begin(), all_contexts.end(), std::bind(context_equals, ctx, std::placeholders::_1));
        if (iter != all_contexts.end())
        {
            current_context = *iter;
        }
    }
}

extern "C"
{

fixie_context FIXIE_APIENTRY fixie_create_context()
{
    std::shared_ptr<fixie::context> ctx = fixie::create_context();
    fixie::set_current_context(ctx.get());
    return ctx.get();
}

void FIXIE_APIENTRY fixie_destroy_context(fixie_context ctx)
{
    fixie::destroy_context(reinterpret_cast<fixie::context*>(ctx));
}

void FIXIE_APIENTRY fixie_set_context(fixie_context ctx)
{
    fixie::set_current_context(reinterpret_cast<fixie::context*>(ctx));
}

void FIXIE_APIENTRY glAlphaFunc(GLenum func, GLclampf ref)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glClearDepthf(GLclampf depth)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glClipPlanef(GLenum plane, const GLfloat *equation)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glColor4f(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glDepthRangef(GLclampf zNear, GLclampf zFar)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glFogf(GLenum pname, GLfloat param)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glFogfv(GLenum pname, const GLfloat *params)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glFrustumf(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glGetClipPlanef(GLenum pname, GLfloat eqn[4])
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glGetFloatv(GLenum pname, GLfloat *params)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glGetLightfv(GLenum light, GLenum pname, GLfloat *params)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glGetMaterialfv(GLenum face, GLenum pname, GLfloat *params)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glGetTexEnvfv(GLenum env, GLenum pname, GLfloat *params)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glGetTexParameterfv(GLenum target, GLenum pname, GLfloat *params)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glLightModelf(GLenum pname, GLfloat param)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glLightModelfv(GLenum pname, const GLfloat *params)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glLightf(GLenum light, GLenum pname, GLfloat param)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glLightfv(GLenum light, GLenum pname, const GLfloat *params)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glLineWidth(GLfloat width)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glLoadMatrixf(const GLfloat *m)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glMaterialf(GLenum face, GLenum pname, GLfloat param)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glMaterialfv(GLenum face, GLenum pname, const GLfloat *params)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glMultMatrixf(const GLfloat *m)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glMultiTexCoord4f(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glNormal3f(GLfloat nx, GLfloat ny, GLfloat nz)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glOrthof(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glPointParameterf(GLenum pname, GLfloat param)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glPointParameterfv(GLenum pname, const GLfloat *params)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glPointSize(GLfloat size)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glPolygonOffset(GLfloat factor, GLfloat units)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glScalef(GLfloat x, GLfloat y, GLfloat z)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glTexEnvf(GLenum target, GLenum pname, GLfloat param)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glTexEnvfv(GLenum target, GLenum pname, const GLfloat *params)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glTexParameterf(GLenum target, GLenum pname, GLfloat param)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glTexParameterfv(GLenum target, GLenum pname, const GLfloat *params)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glTranslatef(GLfloat x, GLfloat y, GLfloat z)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glActiveTexture(GLenum texture)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glAlphaFuncx(GLenum func, GLclampx ref)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glBindBuffer(GLenum target, GLuint buffer)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glBindTexture(GLenum target, GLuint texture)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glBlendFunc(GLenum sfactor, GLenum dfactor)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glBufferData(GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glClear(GLbitfield mask)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glClearColorx(GLclampx red, GLclampx green, GLclampx blue, GLclampx alpha)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glClearDepthx(GLclampx depth)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glClearStencil(GLint s)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glClientActiveTexture(GLenum texture)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glClipPlanex(GLenum plane, const GLfixed *equation)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glColor4ub(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glColor4x(GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glColorPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glCopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glCullFace(GLenum mode)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glDeleteBuffers(GLsizei n, const GLuint *buffers)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glDeleteTextures(GLsizei n, const GLuint *textures)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glDepthFunc(GLenum func)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glDepthMask(GLboolean flag)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glDepthRangex(GLclampx zNear, GLclampx zFar)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glDisable(GLenum cap)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glDisableClientState(GLenum array)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glDrawArrays(GLenum mode, GLint first, GLsizei count)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glEnable(GLenum cap)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glEnableClientState(GLenum array)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glFinish(void)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glFlush(void)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glFogx(GLenum pname, GLfixed param)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glFogxv(GLenum pname, const GLfixed *params)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glFrontFace(GLenum mode)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glFrustumx(GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glGetBooleanv(GLenum pname, GLboolean *params)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glGetBufferParameteriv(GLenum target, GLenum pname, GLint *params)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glGetClipPlanex(GLenum pname, GLfixed eqn[4])
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glGenBuffers(GLsizei n, GLuint *buffers)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glGenTextures(GLsizei n, GLuint *textures)
{
    UNIMPLEMENTED();
}

GLenum FIXIE_APIENTRY glGetError(void)
{
    UNIMPLEMENTED();
    return GL_FALSE;
}

void FIXIE_APIENTRY glGetFixedv(GLenum pname, GLfixed *params)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glGetIntegerv(GLenum pname, GLint *params)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glGetLightxv(GLenum light, GLenum pname, GLfixed *params)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glGetMaterialxv(GLenum face, GLenum pname, GLfixed *params)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glGetPointerv(GLenum pname, GLvoid **params)
{
    UNIMPLEMENTED();
}

const GLubyte * FIXIE_APIENTRY glGetString(GLenum name)
{
    UNIMPLEMENTED();
    return NULL;
}

void FIXIE_APIENTRY glGetTexEnviv(GLenum env, GLenum pname, GLint *params)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glGetTexEnvxv(GLenum env, GLenum pname, GLfixed *params)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glGetTexParameteriv(GLenum target, GLenum pname, GLint *params)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glGetTexParameterxv(GLenum target, GLenum pname, GLfixed *params)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glHint(GLenum target, GLenum mode)
{
    UNIMPLEMENTED();
}

GLboolean FIXIE_APIENTRY glIsBuffer(GLuint buffer)
{
    UNIMPLEMENTED();
    return GL_FALSE;
}

GLboolean FIXIE_APIENTRY glIsEnabled(GLenum cap)
{
    UNIMPLEMENTED();
    return GL_FALSE;
}

GLboolean FIXIE_APIENTRY glIsTexture(GLuint texture)
{
    UNIMPLEMENTED();
    return GL_FALSE;
}

void FIXIE_APIENTRY glLightModelx(GLenum pname, GLfixed param)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glLightModelxv(GLenum pname, const GLfixed *params)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glLightx(GLenum light, GLenum pname, GLfixed param)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glLightxv(GLenum light, GLenum pname, const GLfixed *params)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glLineWidthx(GLfixed width)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glLoadIdentity(void)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glLoadMatrixx(const GLfixed *m)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glLogicOp(GLenum opcode)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glMaterialx(GLenum face, GLenum pname, GLfixed param)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glMaterialxv(GLenum face, GLenum pname, const GLfixed *params)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glMatrixMode(GLenum mode)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glMultMatrixx(const GLfixed *m)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glMultiTexCoord4x(GLenum target, GLfixed s, GLfixed t, GLfixed r, GLfixed q)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glNormal3x(GLfixed nx, GLfixed ny, GLfixed nz)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glNormalPointer(GLenum type, GLsizei stride, const GLvoid *pointer)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glOrthox(GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glPixelStorei(GLenum pname, GLint param)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glPointParameterx(GLenum pname, GLfixed param)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glPointParameterxv(GLenum pname, const GLfixed *params)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glPointSizex(GLfixed size)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glPolygonOffsetx(GLfixed factor, GLfixed units)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glPopMatrix(void)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glPushMatrix(void)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glRotatex(GLfixed angle, GLfixed x, GLfixed y, GLfixed z)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glSampleCoverage(GLclampf value, GLboolean invert)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glSampleCoveragex(GLclampx value, GLboolean invert)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glScalex(GLfixed x, GLfixed y, GLfixed z)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glScissor(GLint x, GLint y, GLsizei width, GLsizei height)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glShadeModel(GLenum mode)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glStencilFunc(GLenum func, GLint ref, GLuint mask)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glStencilMask(GLuint mask)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glStencilOp(GLenum fail, GLenum zfail, GLenum zpass)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glTexCoordPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glTexEnvi(GLenum target, GLenum pname, GLint param)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glTexEnvx(GLenum target, GLenum pname, GLfixed param)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glTexEnviv(GLenum target, GLenum pname, const GLint *params)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glTexEnvxv(GLenum target, GLenum pname, const GLfixed *params)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glTexParameteri(GLenum target, GLenum pname, GLint param)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glTexParameterx(GLenum target, GLenum pname, GLfixed param)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glTexParameteriv(GLenum target, GLenum pname, const GLint *params)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glTexParameterxv(GLenum target, GLenum pname, const GLfixed *params)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glTranslatex(GLfixed x, GLfixed y, GLfixed z)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glVertexPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glViewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
    UNIMPLEMENTED();
}

}
