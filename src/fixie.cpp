#include <stddef.h>
#include <vector>

#include "fixie.h"
#include "fixie_gl_es.h"
#include "fixie_gl_es_ext.h"

#include "debug.hpp"
#include "context.hpp"
#include "fixed_point.hpp"
#include "exceptions.hpp"

namespace fixie
{
    static void set_material_parameters(GLenum face, GLenum pname, const real_ptr& params, bool vector_call)
    {
        try
        {
            std::shared_ptr<context> ctx = get_current_context();

            std::vector<material*> materials;
            switch (face)
            {
            case GL_FRONT:          materials.push_back(&ctx->front_material());                                             break;
            case GL_BACK:                                                        materials.push_back(&ctx->back_material()); break;
            case GL_FRONT_AND_BACK: materials.push_back(&ctx->front_material()); materials.push_back(&ctx->back_material()); break;
            default:                throw invalid_enum_error("unknown face name.");
            }

            switch (pname)
            {
            case GL_AMBIENT:
                if (!vector_call)
                {
                    throw fixie::invalid_enum_error("multi-valued parameter name, GL_AMBIENT, passed to non-vector material function.");
                }
                for (auto mat = begin(materials); mat != end(materials); mat++)
                {
                    (*mat)->ambient() = color(params.as_float(0), params.as_float(1), params.as_float(2), params.as_float(3));
                }
                break;

            case GL_DIFFUSE:
                if (!vector_call)
                {
                    throw invalid_enum_error("multi-valued parameter name, GL_DIFFUSE, passed to non-vector material function.");
                }
                for (auto mat = begin(materials); mat != end(materials); mat++)
                {
                    (*mat)->diffuse() = color(params.as_float(0), params.as_float(1), params.as_float(2), params.as_float(3));
                }
                break;

            case GL_AMBIENT_AND_DIFFUSE:
                if (!vector_call)
                {
                    throw invalid_enum_error("multi-valued parameter name, GL_AMBIENT_AND_DIFFUSE, passed to non-vector material function.");
                }
                for (auto mat = begin(materials); mat != end(materials); mat++)
                {
                    (*mat)->ambient() = color(params.as_float(0), params.as_float(1), params.as_float(2), params.as_float(3));
                    (*mat)->diffuse() = color(params.as_float(0), params.as_float(1), params.as_float(2), params.as_float(3));
                }
                break;

            case GL_SPECULAR:
                if (!vector_call)
                {
                    throw invalid_enum_error("multi-valued parameter name, GL_SPECULAR, passed to non-vector material function.");
                }
                for (auto mat = begin(materials); mat != end(materials); mat++)
                {
                    (*mat)->specular() = color(params.as_float(0), params.as_float(1), params.as_float(2), params.as_float(3));
                }
                break;

            case GL_EMISSION:
                if (!vector_call)
                {
                    throw invalid_enum_error("multi-valued parameter name, GL_EMISSION, passed to non-vector material function.");
                }
                for (auto mat = begin(materials); mat != end(materials); mat++)
                {
                    (*mat)->emissive() = color(params.as_float(0), params.as_float(1), params.as_float(2), params.as_float(3));
                }
                break;

            case GL_SHININESS:
                if (params.as_float(0) < 0.0f || params.as_float(0) > 128.0f)
                {
                    throw invalid_value_error("shininess must be in the range [0, 128.0].");
                }
                for (auto mat = begin(materials); mat != end(materials); mat++)
                {
                    (*mat)->specular_exponent() = params.as_float(0);
                }
                break;

            default:
                throw fixie::invalid_enum_error("unknown parameter name.");
            }
        }
        catch (fixie::gl_error e)
        {
            log_gl_error(e);
        }
        catch (fixie::context_error e)
        {
            log_context_erorr(e);
        }
        catch (...)
        {
            UNREACHABLE();
        }
    }
}

extern "C"
{

fixie_context FIXIE_APIENTRY fixie_create_context()
{
    try
    {
        std::shared_ptr<fixie::context> ctx = fixie::create_context();
        fixie::set_current_context(ctx.get());
        return ctx.get();
    }
    catch (fixie::context_error e)
    {
        fixie::log_context_error(e);
        return nullptr;
    }
    catch (...)
    {
        UNREACHABLE();
        return nullptr;
    }
}

void FIXIE_APIENTRY fixie_destroy_context(fixie_context ctx)
{
    try
    {
        fixie::destroy_context(reinterpret_cast<fixie::context*>(ctx));
    }
    catch (...)
    {
        UNREACHABLE();
    }
}

void FIXIE_APIENTRY fixie_set_context(fixie_context ctx)
{
    try
    {
        fixie::set_current_context(reinterpret_cast<fixie::context*>(ctx));
    }
    catch (...)
    {
        UNREACHABLE();
    }
}

fixie_context FIXIE_APIENTRY fixie_get_context()
{
    try
    {
        std::shared_ptr<fixie::context> ctx = fixie::get_current_context();
        return ctx.get();
    }
    catch (fixie::context_error e)
    {
        fixie::log_context_error(e);
        return nullptr;
    }
    catch (...)
    {
        UNREACHABLE();
    }
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
    fixie::set_material_parameters(face, pname, &param, false);
}

void FIXIE_APIENTRY glMaterialfv(GLenum face, GLenum pname, const GLfloat *params)
{
    fixie::set_material_parameters(face, pname, params, true);
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
    try
    {
        std::shared_ptr<fixie::context> ctx = fixie::get_current_context();

        GLenum error = ctx->error();
        ctx->error() = GL_NO_ERROR;
        return error;
    }
    catch (fixie::context_error e)
    {
        fixie::log_context_error(e);
        return GL_NO_ERROR;
    }
    catch (...)
    {
        UNREACHABLE();
        return GL_NO_ERROR;
    }
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
    fixie::set_material_parameters(face, pname, &param, false);
}

void FIXIE_APIENTRY glMaterialxv(GLenum face, GLenum pname, const GLfixed *params)
{
    fixie::set_material_parameters(face, pname, params, true);
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
