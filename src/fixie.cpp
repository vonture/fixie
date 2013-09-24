#include <stddef.h>
#include <set>
#include <algorithm>
#include <functional>

#define GL_API
#include <GLES/gl.h>

#include "fixie.h"

#include "debug.hpp"
#include "context.hpp"

namespace fixie
{
    std::shared_ptr<context> current_context;
    std::set< std::shared_ptr<context> > all_contexts;

    std::shared_ptr<context> create_context()
    {
        std::shared_ptr<context> ctx(new context());
        all_contexts.insert(ctx);
        return ctx;
    }

    bool context_equals(context* a, std::shared_ptr<context> b)
    {
        return a == b.get();
    }

    void destroy_context(context* ctx)
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

    std::shared_ptr<context> get_current_context()
    {
        if (!current_context && all_contexts.size() == 0)
        {
            current_context = create_context();
        }

        return current_context;
    }

    void set_current_context(context* ctx)
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

fixie_context fixie_create_context()
{
    std::shared_ptr<fixie::context> ctx = fixie::create_context();
    fixie::set_current_context(ctx.get());
    return ctx.get();
}

void fixie_destroy_context(fixie_context ctx)
{
    fixie::destroy_context(reinterpret_cast<fixie::context*>(ctx));
}

void fixie_set_context(fixie_context ctx)
{
    fixie::set_current_context(reinterpret_cast<fixie::context*>(ctx));
}

void GL_APIENTRY glAlphaFunc(GLenum func, GLclampf ref)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glClearDepthf(GLclampf depth)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glClipPlanef(GLenum plane, const GLfloat *equation)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glColor4f(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glDepthRangef(GLclampf zNear, GLclampf zFar)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glFogf(GLenum pname, GLfloat param)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glFogfv(GLenum pname, const GLfloat *params)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glFrustumf(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glGetClipPlanef(GLenum pname, GLfloat eqn[4])
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glGetFloatv(GLenum pname, GLfloat *params)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glGetLightfv(GLenum light, GLenum pname, GLfloat *params)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glGetMaterialfv(GLenum face, GLenum pname, GLfloat *params)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glGetTexEnvfv(GLenum env, GLenum pname, GLfloat *params)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glGetTexParameterfv(GLenum target, GLenum pname, GLfloat *params)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glLightModelf(GLenum pname, GLfloat param)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glLightModelfv(GLenum pname, const GLfloat *params)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glLightf(GLenum light, GLenum pname, GLfloat param)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glLightfv(GLenum light, GLenum pname, const GLfloat *params)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glLineWidth(GLfloat width)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glLoadMatrixf(const GLfloat *m)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glMaterialf(GLenum face, GLenum pname, GLfloat param)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glMaterialfv(GLenum face, GLenum pname, const GLfloat *params)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glMultMatrixf(const GLfloat *m)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glMultiTexCoord4f(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glNormal3f(GLfloat nx, GLfloat ny, GLfloat nz)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glOrthof(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glPointParameterf(GLenum pname, GLfloat param)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glPointParameterfv(GLenum pname, const GLfloat *params)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glPointSize(GLfloat size)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glPolygonOffset(GLfloat factor, GLfloat units)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glScalef(GLfloat x, GLfloat y, GLfloat z)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glTexEnvf(GLenum target, GLenum pname, GLfloat param)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glTexEnvfv(GLenum target, GLenum pname, const GLfloat *params)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glTexParameterf(GLenum target, GLenum pname, GLfloat param)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glTexParameterfv(GLenum target, GLenum pname, const GLfloat *params)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glTranslatef(GLfloat x, GLfloat y, GLfloat z)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glActiveTexture(GLenum texture)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glAlphaFuncx(GLenum func, GLclampx ref)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glBindBuffer(GLenum target, GLuint buffer)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glBindTexture(GLenum target, GLuint texture)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glBlendFunc(GLenum sfactor, GLenum dfactor)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glBufferData(GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glClear(GLbitfield mask)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glClearColorx(GLclampx red, GLclampx green, GLclampx blue, GLclampx alpha)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glClearDepthx(GLclampx depth)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glClearStencil(GLint s)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glClientActiveTexture(GLenum texture)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glClipPlanex(GLenum plane, const GLfixed *equation)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glColor4ub(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glColor4x(GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glColorPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glCopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glCullFace(GLenum mode)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glDeleteBuffers(GLsizei n, const GLuint *buffers)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glDeleteTextures(GLsizei n, const GLuint *textures)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glDepthFunc(GLenum func)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glDepthMask(GLboolean flag)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glDepthRangex(GLclampx zNear, GLclampx zFar)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glDisable(GLenum cap)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glDisableClientState(GLenum array)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glDrawArrays(GLenum mode, GLint first, GLsizei count)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glEnable(GLenum cap)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glEnableClientState(GLenum array)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glFinish(void)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glFlush(void)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glFogx(GLenum pname, GLfixed param)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glFogxv(GLenum pname, const GLfixed *params)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glFrontFace(GLenum mode)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glFrustumx(GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glGetBooleanv(GLenum pname, GLboolean *params)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glGetBufferParameteriv(GLenum target, GLenum pname, GLint *params)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glGetClipPlanex(GLenum pname, GLfixed eqn[4])
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glGenBuffers(GLsizei n, GLuint *buffers)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glGenTextures(GLsizei n, GLuint *textures)
{
    UNIMPLEMENTED();
}

GLenum GL_APIENTRY glGetError(void)
{
    UNIMPLEMENTED();
    return GL_FALSE;
}

void GL_APIENTRY glGetFixedv(GLenum pname, GLfixed *params)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glGetIntegerv(GLenum pname, GLint *params)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glGetLightxv(GLenum light, GLenum pname, GLfixed *params)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glGetMaterialxv(GLenum face, GLenum pname, GLfixed *params)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glGetPointerv(GLenum pname, GLvoid **params)
{
    UNIMPLEMENTED();
}

const GLubyte * GL_APIENTRY glGetString(GLenum name)
{
    UNIMPLEMENTED();
    return NULL;
}

void GL_APIENTRY glGetTexEnviv(GLenum env, GLenum pname, GLint *params)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glGetTexEnvxv(GLenum env, GLenum pname, GLfixed *params)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glGetTexParameteriv(GLenum target, GLenum pname, GLint *params)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glGetTexParameterxv(GLenum target, GLenum pname, GLfixed *params)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glHint(GLenum target, GLenum mode)
{
    UNIMPLEMENTED();
}

GLboolean GL_APIENTRY glIsBuffer(GLuint buffer)
{
    UNIMPLEMENTED();
    return GL_FALSE;
}

GLboolean GL_APIENTRY glIsEnabled(GLenum cap)
{
    UNIMPLEMENTED();
    return GL_FALSE;
}

GLboolean GL_APIENTRY glIsTexture(GLuint texture)
{
    UNIMPLEMENTED();
    return GL_FALSE;
}

void GL_APIENTRY glLightModelx(GLenum pname, GLfixed param)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glLightModelxv(GLenum pname, const GLfixed *params)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glLightx(GLenum light, GLenum pname, GLfixed param)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glLightxv(GLenum light, GLenum pname, const GLfixed *params)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glLineWidthx(GLfixed width)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glLoadIdentity(void)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glLoadMatrixx(const GLfixed *m)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glLogicOp(GLenum opcode)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glMaterialx(GLenum face, GLenum pname, GLfixed param)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glMaterialxv(GLenum face, GLenum pname, const GLfixed *params)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glMatrixMode(GLenum mode)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glMultMatrixx(const GLfixed *m)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glMultiTexCoord4x(GLenum target, GLfixed s, GLfixed t, GLfixed r, GLfixed q)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glNormal3x(GLfixed nx, GLfixed ny, GLfixed nz)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glNormalPointer(GLenum type, GLsizei stride, const GLvoid *pointer)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glOrthox(GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glPixelStorei(GLenum pname, GLint param)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glPointParameterx(GLenum pname, GLfixed param)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glPointParameterxv(GLenum pname, const GLfixed *params)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glPointSizex(GLfixed size)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glPolygonOffsetx(GLfixed factor, GLfixed units)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glPopMatrix(void)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glPushMatrix(void)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glRotatex(GLfixed angle, GLfixed x, GLfixed y, GLfixed z)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glSampleCoverage(GLclampf value, GLboolean invert)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glSampleCoveragex(GLclampx value, GLboolean invert)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glScalex(GLfixed x, GLfixed y, GLfixed z)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glScissor(GLint x, GLint y, GLsizei width, GLsizei height)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glShadeModel(GLenum mode)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glStencilFunc(GLenum func, GLint ref, GLuint mask)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glStencilMask(GLuint mask)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glStencilOp(GLenum fail, GLenum zfail, GLenum zpass)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glTexCoordPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glTexEnvi(GLenum target, GLenum pname, GLint param)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glTexEnvx(GLenum target, GLenum pname, GLfixed param)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glTexEnviv(GLenum target, GLenum pname, const GLint *params)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glTexEnvxv(GLenum target, GLenum pname, const GLfixed *params)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glTexParameteri(GLenum target, GLenum pname, GLint param)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glTexParameterx(GLenum target, GLenum pname, GLfixed param)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glTexParameteriv(GLenum target, GLenum pname, const GLint *params)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glTexParameterxv(GLenum target, GLenum pname, const GLfixed *params)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glTranslatex(GLfixed x, GLfixed y, GLfixed z)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glVertexPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
{
    UNIMPLEMENTED();
}

void GL_APIENTRY glViewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
    UNIMPLEMENTED();
}

}
