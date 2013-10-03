#include <stddef.h>
#include <vector>

#include "fixie.h"
#include "fixie_gl_es.h"
#include "fixie_gl_es_ext.h"

#include "debug.hpp"
#include "context.hpp"
#include "fixed_point.hpp"
#include "exceptions.hpp"
#include "util.hpp"

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
            case GL_FRONT:          materials.push_back(&ctx->state().front_material());                                                     break;
            case GL_BACK:                                                                materials.push_back(&ctx->state().back_material()); break;
            case GL_FRONT_AND_BACK: materials.push_back(&ctx->state().front_material()); materials.push_back(&ctx->state().back_material()); break;
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
                throw invalid_enum_error("unknown parameter name.");
            }
        }
        catch (gl_error e)
        {
            log_gl_error(e);
        }
        catch (context_error e)
        {
            log_context_error(e);
        }
        catch (...)
        {
            UNREACHABLE();
        }
    }

    static void set_light_parameters(GLenum l, GLenum pname, const real_ptr& params, bool vector_call)
    {
        try
        {
            std::shared_ptr<context> ctx = get_current_context();

            size_t max_lights = ctx->state().light_count();
            if (l < GL_LIGHT0 || (l - GL_LIGHT0) > max_lights)
            {
                throw invalid_enum_error(format("invalid light, must be between GL_LIGHT0 and GL_LIGHT%u.", max_lights - 1));
            }
            light& light = ctx->state().lights(l - GL_LIGHT0);

            switch (pname)
            {
            case GL_AMBIENT:
                if (!vector_call)
                {
                    throw invalid_enum_error("multi-valued parameter name, GL_AMBIENT, passed to non-vector light function.");
                }
                light.ambient() = color(params.as_float(0), params.as_float(1), params.as_float(2), params.as_float(3));
                break;

            case GL_DIFFUSE:
                if (!vector_call)
                {
                    throw invalid_enum_error("multi-valued parameter name, GL_DIFFUSE, passed to non-vector light function.");
                }
                light.diffuse() = color(params.as_float(0), params.as_float(1), params.as_float(2), params.as_float(3));
                break;

            case GL_SPECULAR:
                if (!vector_call)
                {
                    throw invalid_enum_error("multi-valued parameter name, GL_SPECULAR, passed to non-vector light function.");
                }
                light.specular() = color(params.as_float(0), params.as_float(1), params.as_float(2), params.as_float(3));
                break;

            case GL_POSITION:
                if (!vector_call)
                {
                    throw invalid_enum_error("multi-valued parameter name, GL_POSITION, passed to non-vector light function.");
                }
                light.position() = vector4(params.as_float(0), params.as_float(1), params.as_float(2), params.as_float(3));
                break;

            case GL_SPOT_DIRECTION:
                if (!vector_call)
                {
                    throw invalid_enum_error("multi-valued parameter name, GL_SPOT_DIRECTION, passed to non-vector light function.");
                }
                light.spot_direction() = vector3(params.as_float(0), params.as_float(1), params.as_float(2));
                break;

            case GL_SPOT_EXPONENT:
                if (params.as_float(0) < 0.0f || params.as_float(0) > 128.0f)
                {
                    throw invalid_value_error("spot light exponent must be in the range [0, 128.0].");
                }
                light.spot_exponent() = params.as_float(0);
                break;

            case GL_SPOT_CUTOFF:
                if ((params.as_float(0) < 0.0f || params.as_float(0) > 128.0f) && params.as_float(0) != 180.0f)
                {
                    throw invalid_value_error("spot light cutoff angle must be in the range [0, 90.0] or 180.0.");
                }
                light.spot_cutoff() = params.as_float(0);
                break;

            case GL_CONSTANT_ATTENUATION:
                if (params.as_float(0) < 0.0f)
                {
                    throw invalid_value_error("spot light constant attenuation must be at least 0.0.");
                }
                light.constant_attenuation() = params.as_float(0);
                break;

            case GL_LINEAR_ATTENUATION:
                if (params.as_float(0) < 0.0f)
                {
                    throw invalid_value_error("spot light linear attenuation must be at least 0.0.");
                }
                light.linear_attenuation() = params.as_float(0);
                break;

            case GL_QUADRATIC_ATTENUATION:
                if (params.as_float(0) < 0.0f)
                {
                    throw invalid_value_error("spot light quadratic attenuation must be at least 0.0.");
                }
                light.quadratic_attenuation() = params.as_float(0);
                break;

            default:
                throw invalid_enum_error("unknown parameter name.");
            }
        }
        catch (gl_error e)
        {
            log_gl_error(e);
        }
        catch (context_error e)
        {
            log_context_error(e);
        }
        catch (...)
        {
            UNREACHABLE();
        }
    }

    static void set_light_model_parameters(GLenum pname, const real_ptr& params, bool vector_call)
    {
        try
        {
            std::shared_ptr<context> ctx = get_current_context();

            switch (pname)
            {
            case GL_LIGHT_MODEL_AMBIENT:
                if (!vector_call)
                {
                    throw invalid_enum_error("multi-valued parameter name, GL_LIGHT_MODEL_AMBIENT, passed to non-vector light model function.");
                }
                ctx->state().light_model().ambient_color() = color(params.as_float(0), params.as_float(1), params.as_float(2), params.as_float(3));
                break;

            case GL_LIGHT_MODEL_TWO_SIDE:
                ctx->state().light_model().two_sided_lighting() = (params.as_float(0) != 0.0f);
                break;

            default:
                throw invalid_enum_error("unknown parameter name.");
            }
        }
        catch (gl_error e)
        {
            log_gl_error(e);
        }
        catch (context_error e)
        {
            log_context_error(e);
        }
        catch (...)
        {
            UNREACHABLE();
        }
    }

    static void set_clip_plane(GLenum p, const real_ptr& params)
    {
        try
        {
            std::shared_ptr<context> ctx = get_current_context();

            size_t max_clip_planes = ctx->state().clip_plane_count();
            if (p < GL_CLIP_PLANE0 || (p - GL_CLIP_PLANE0) > max_clip_planes)
            {
                throw invalid_enum_error(format("invalid clip plane, must be between GL_CLIP_PLANE0 and GL_CLIP_PLANE%u.", max_clip_planes - 1));
            }

            ctx->state().clip_plane(p - GL_CLIP_PLANE0) = vector4(params.as_float(0), params.as_float(1), params.as_float(2), params.as_float(3));
        }
        catch (gl_error e)
        {
            log_gl_error(e);
        }
        catch (context_error e)
        {
            log_context_error(e);
        }
        catch (...)
        {
            UNREACHABLE();
        }
    }

    static void set_matrix(const matrix4& matrix, bool multiply)
    {
        try
        {
            std::shared_ptr<context> ctx = get_current_context();

            matrix_stack& stack = ctx->state().active_matrix_stack();

            if (multiply)
            {
                stack.top() *= matrix;
            }
            else
            {
                stack.top() = matrix;
            }
        }
        catch (gl_error e)
        {
            log_gl_error(e);
        }
        catch (context_error e)
        {
            log_context_error(e);
        }
        catch (...)
        {
            UNREACHABLE();
        }
    }

    static void set_matrix(const real_ptr& m, bool multiply)
    {
        fixie::matrix4 mat(m.as_float( 0), m.as_float( 4), m.as_float( 8), m.as_float(12),
                           m.as_float( 1), m.as_float( 5), m.as_float( 9), m.as_float(13),
                           m.as_float( 2), m.as_float( 6), m.as_float(10), m.as_float(14),
                           m.as_float( 3), m.as_float( 7), m.as_float(11), m.as_float(15));
        set_matrix(mat, multiply);
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
    fixie::set_clip_plane(plane, equation);
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
    try
    {
        if (zNear <= 0.0f || zFar < 0.0f)
        {
            throw fixie::invalid_value_error(fixie::format("zNear (%g provided) and zFar (%g provided) must be greater than 0.0.", zNear, zFar));
        }

        if (left == right)
        {
            throw fixie::invalid_value_error(fixie::format("left (%g provided) and right (%g provided) cannot be equal.", left, right));
        }

        if (bottom == top)
        {
            throw fixie::invalid_value_error(fixie::format("bottom (%g provided) and top (%g provided) cannot be equal.", bottom, top));
        }

        if (zNear == zFar)
        {
            throw fixie::invalid_value_error(fixie::format("zNear (%g provided) and zFar (%g provided) cannot be equal.", zNear, zFar));
        }

        fixie::set_matrix(fixie::matrix4::frustum(left, right, bottom, top, zNear, zFar), true);
    }
    catch (fixie::gl_error e)
    {
        fixie::log_gl_error(e);
    }
    catch (...)
    {
        UNREACHABLE();
    }
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
    fixie::set_light_model_parameters(pname, &param, false);
}

void FIXIE_APIENTRY glLightModelfv(GLenum pname, const GLfloat *params)
{
    fixie::set_light_model_parameters(pname, params, true);
}

void FIXIE_APIENTRY glLightf(GLenum light, GLenum pname, GLfloat param)
{
    fixie::set_light_parameters(light, pname, &param, false);
}

void FIXIE_APIENTRY glLightfv(GLenum light, GLenum pname, const GLfloat *params)
{
    fixie::set_light_parameters(light, pname, params, true);
}

void FIXIE_APIENTRY glLineWidth(GLfloat width)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glLoadMatrixf(const GLfloat *m)
{
    fixie::set_matrix(m, false);
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
    fixie::set_matrix(m, true);
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
    try
    {
        if (left == right)
        {
            throw fixie::invalid_value_error(fixie::format("left (%g provided) and right (%g provided) cannot be equal.", left, right));
        }

        if (bottom == top)
        {
            throw fixie::invalid_value_error(fixie::format("bottom (%g provided) and top (%g provided) cannot be equal.", bottom, top));
        }

        if (zNear == zFar)
        {
            throw fixie::invalid_value_error(fixie::format("zNear (%g provided) and zFar (%g provided) cannot be equal.", zNear, zFar));
        }

        fixie::set_matrix(fixie::matrix4::ortho(left, right, bottom, top, zNear, zFar), true);
    }
    catch (fixie::gl_error e)
    {
        fixie::log_gl_error(e);
    }
    catch (...)
    {
        UNREACHABLE();
    }
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
    fixie::set_matrix(fixie::matrix4::rotate(angle, fixie::vector3(x, y, z)), true);
}

void FIXIE_APIENTRY glScalef(GLfloat x, GLfloat y, GLfloat z)
{
    fixie::set_matrix(fixie::matrix4::scale(fixie::vector3(x, y, z)), true);
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
    fixie::set_matrix(fixie::matrix4::translate(fixie::vector3(x, y, z)), true);
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
    fixie::set_clip_plane(plane, equation);
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
    try
    {
        std::shared_ptr<fixie::context> ctx = fixie::get_current_context();

        if (n < 0)
        {
            throw fixie::invalid_value_error(fixie::format("invalid number of buffers given (%i), at least 0 required.", n));
        }

        for (GLsizei i = 0; i < n; ++i)
        {
            ctx->state().delete_buffer(buffers[i]);
        }
    }
    catch (fixie::gl_error e)
    {
        fixie::log_gl_error(e);
    }
    catch (fixie::context_error e)
    {
        fixie::log_context_error(e);
    }
    catch (...)
    {
        UNREACHABLE();
    }
}

void FIXIE_APIENTRY glDeleteTextures(GLsizei n, const GLuint *textures)
{
    try
    {
        std::shared_ptr<fixie::context> ctx = fixie::get_current_context();

        if (n < 0)
        {
            throw fixie::invalid_value_error(fixie::format("invalid number of textures given (%i), at least 0 required.", n));
        }

        for (GLsizei i = 0; i < n; ++i)
        {
            ctx->state().delete_texture(textures[i]);
        }
    }
    catch (fixie::gl_error e)
    {
        fixie::log_gl_error(e);
    }
    catch (fixie::context_error e)
    {
        fixie::log_context_error(e);
    }
    catch (...)
    {
        UNREACHABLE();
    }
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
    try
    {
        if (fixie::fixed_to_float(zNear) <= 0.0f || fixie::fixed_to_float(zFar) < 0.0f)
        {
            throw fixie::invalid_value_error(fixie::format("zNear (%g provided) and zFar (%g provided) must be greater than 0.0.",
                                                           fixie::fixed_to_float(zNear), fixie::fixed_to_float(zFar)));
        }

        if (fixie::fixed_to_float(left) == fixie::fixed_to_float(right))
        {
            throw fixie::invalid_value_error(fixie::format("left (%g provided) and right (%g provided) cannot be equal.",
                                                           fixie::fixed_to_float(left), fixie::fixed_to_float(right)));
        }

        if (fixie::fixed_to_float(bottom) == fixie::fixed_to_float(top))
        {
            throw fixie::invalid_value_error(fixie::format("bottom (%g provided) and top (%g provided) cannot be equal.",
                                                           fixie::fixed_to_float(bottom), fixie::fixed_to_float(top)));
        }

        if (fixie::fixed_to_float(zNear) == fixie::fixed_to_float(zFar))
        {
            throw fixie::invalid_value_error(fixie::format("zNear (%g provided) and zFar (%g provided) cannot be equal.",
                                                           fixie::fixed_to_float(zNear), fixie::fixed_to_float(zFar)));
        }

        fixie::set_matrix(fixie::matrix4::frustum(fixie::fixed_to_float(left), fixie::fixed_to_float(right), fixie::fixed_to_float(bottom), fixie::fixed_to_float(top),
                                                  fixie::fixed_to_float(zNear), fixie::fixed_to_float(zFar)),
                          true);
    }
    catch (fixie::gl_error e)
    {
        fixie::log_gl_error(e);
    }
    catch (...)
    {
        UNREACHABLE();
    }
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
    try
    {
        std::shared_ptr<fixie::context> ctx = fixie::get_current_context();

        if (n < 0)
        {
            throw fixie::invalid_value_error(fixie::format("invalid number of buffers given (%i), at least 0 required.", n));
        }

        for (GLsizei i = 0; i < n; ++i)
        {
            buffers[i] = 0;
        }

        try
        {
            for (GLsizei i = 0; i < n; ++i)
            {
                buffers[i] = ctx->create_buffer();
            }
        }
        catch (...)
        {
            try
            {
                for (GLsizei i = 0; i < n; ++i)
                {
                    if (buffers[i])
                    {
                        ctx->state().delete_buffer(buffers[i]);
                    }
                }
            }
            catch (...)
            {
                // error while deleting a buffer, ignore it
            }

            throw;
        }
    }
    catch (fixie::gl_error e)
    {
        fixie::log_gl_error(e);
    }
    catch (fixie::context_error e)
    {
        fixie::log_context_error(e);
    }
    catch (...)
    {
        UNREACHABLE();
    }
}

void FIXIE_APIENTRY glGenTextures(GLsizei n, GLuint *textures)
{
    try
    {
        std::shared_ptr<fixie::context> ctx = fixie::get_current_context();

        if (n < 0)
        {
            throw fixie::invalid_value_error(fixie::format("invalid number of textures given (%i), at least 0 required.", n));
        }

        for (GLsizei i = 0; i < n; ++i)
        {
            textures[i] = 0;
        }

        try
        {
            for (GLsizei i = 0; i < n; ++i)
            {
                textures[i] = ctx->create_texture();
            }
        }
        catch (...)
        {
            try
            {
                for (GLsizei i = 0; i < n; ++i)
                {
                    if (textures[i])
                    {
                        ctx->state().delete_texture(textures[i]);
                    }
                }
            }
            catch (...)
            {
                // error while deleting a texture, ignore it
            }

            throw;
        }
    }
    catch (fixie::gl_error e)
    {
        fixie::log_gl_error(e);
    }
    catch (fixie::context_error e)
    {
        fixie::log_context_error(e);
    }
    catch (...)
    {
        UNREACHABLE();
    }
}

GLenum FIXIE_APIENTRY glGetError(void)
{
    try
    {
        std::shared_ptr<fixie::context> ctx = fixie::get_current_context();

        GLenum error = ctx->state().error();
        ctx->state().error() = GL_NO_ERROR;
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
    try
    {
        std::shared_ptr<fixie::context> ctx = fixie::get_current_context();

        std::shared_ptr<fixie::buffer> buf = ctx->state().buffer(buffer);

        return (buf != nullptr) ? GL_TRUE : GL_FALSE;
    }
    catch (fixie::gl_error e)
    {
        fixie::log_gl_error(e);
        return GL_FALSE;
    }
    catch (fixie::context_error e)
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

GLboolean FIXIE_APIENTRY glIsEnabled(GLenum cap)
{
    UNIMPLEMENTED();
    return GL_FALSE;
}

GLboolean FIXIE_APIENTRY glIsTexture(GLuint texture)
{
    try
    {
        std::shared_ptr<fixie::context> ctx = fixie::get_current_context();

        std::shared_ptr<fixie::texture> tex = ctx->state().texture(texture);

        return (tex != nullptr) ? GL_TRUE : GL_FALSE;
    }
    catch (fixie::gl_error e)
    {
        fixie::log_gl_error(e);
        return GL_FALSE;
    }
    catch (fixie::context_error e)
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

void FIXIE_APIENTRY glLightModelx(GLenum pname, GLfixed param)
{
    fixie::set_light_model_parameters(pname, &param, false);
}

void FIXIE_APIENTRY glLightModelxv(GLenum pname, const GLfixed *params)
{
    fixie::set_light_model_parameters(pname, params, true);
}

void FIXIE_APIENTRY glLightx(GLenum light, GLenum pname, GLfixed param)
{
    fixie::set_light_parameters(light, pname, &param, false);
}

void FIXIE_APIENTRY glLightxv(GLenum light, GLenum pname, const GLfixed *params)
{
    fixie::set_light_parameters(light, pname, params, true);
}

void FIXIE_APIENTRY glLineWidthx(GLfixed width)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glLoadIdentity(void)
{
    fixie::set_matrix(fixie::matrix4::identity(), false);
}

void FIXIE_APIENTRY glLoadMatrixx(const GLfixed *m)
{
    fixie::set_matrix(m, false);
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
    try
    {
        std::shared_ptr<fixie::context> ctx = fixie::get_current_context();

        switch (mode)
        {
        case GL_TEXTURE:
        case GL_MODELVIEW:
        case GL_PROJECTION:
            break;

        default:
            throw fixie::invalid_enum_error("unknown matrix mode.");
        }

        ctx->state().matrix_mode() = mode;
    }
    catch (fixie::gl_error e)
    {
        fixie::log_gl_error(e);
    }
    catch (fixie::context_error e)
    {
        fixie::log_context_error(e);
    }
    catch (...)
    {
        UNREACHABLE();
    }
}

void FIXIE_APIENTRY glMultMatrixx(const GLfixed *m)
{
    fixie::set_matrix(m, true);
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
    try
    {
        if (fixie::fixed_to_float(left) == fixie::fixed_to_float(right))
        {
            throw fixie::invalid_value_error(fixie::format("left (%g provided) and right (%g provided) cannot be equal.",
                                                           fixie::fixed_to_float(left), fixie::fixed_to_float(right)));
        }

        if (fixie::fixed_to_float(bottom) == fixie::fixed_to_float(top))
        {
            throw fixie::invalid_value_error(fixie::format("bottom (%g provided) and top (%g provided) cannot be equal.",
                                                           fixie::fixed_to_float(bottom), fixie::fixed_to_float(top)));
        }

        if (fixie::fixed_to_float(zNear) == fixie::fixed_to_float(zFar))
        {
            throw fixie::invalid_value_error(fixie::format("zNear (%g provided) and zFar (%g provided) cannot be equal.",
                                                           fixie::fixed_to_float(zNear), fixie::fixed_to_float(zFar)));
        }

        fixie::set_matrix(fixie::matrix4::ortho(fixie::fixed_to_float(left), fixie::fixed_to_float(right), fixie::fixed_to_float(bottom), fixie::fixed_to_float(top),
                                            fixie::fixed_to_float(zNear), fixie::fixed_to_float(zFar)),
                          true);
    }
    catch (fixie::gl_error e)
    {
        fixie::log_gl_error(e);
    }
    catch (...)
    {
        UNREACHABLE();
    }
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
    try
    {
        std::shared_ptr<fixie::context> ctx = fixie::get_current_context();

        fixie::matrix_stack& active_stack = ctx->state().active_matrix_stack();
        if (active_stack.size() <= 1)
        {
            throw fixie::stack_overflow_error(fixie::format("active matrix stack has only %u matrices.", active_stack.size()));
        }
        active_stack.pop();
    }
    catch (fixie::gl_error e)
    {
        fixie::log_gl_error(e);
    }
    catch (fixie::context_error e)
    {
        fixie::log_context_error(e);
    }
    catch (...)
    {
        UNREACHABLE();
    }
}

void FIXIE_APIENTRY glPushMatrix(void)
{
    try
    {
        std::shared_ptr<fixie::context> ctx = fixie::get_current_context();

        fixie::matrix_stack& active_stack = ctx->state().active_matrix_stack();
        active_stack.push();
    }
    catch (fixie::gl_error e)
    {
        fixie::log_gl_error(e);
    }
    catch (fixie::context_error e)
    {
        fixie::log_context_error(e);
    }
    catch (...)
    {
        UNREACHABLE();
    }
}

void FIXIE_APIENTRY glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels)
{
    UNIMPLEMENTED();
}

void FIXIE_APIENTRY glRotatex(GLfixed angle, GLfixed x, GLfixed y, GLfixed z)
{
    fixie::set_matrix(fixie::matrix4::rotate(fixie::fixed_to_float(angle),
                                             fixie::vector3(fixie::fixed_to_float(x), fixie::fixed_to_float(y), fixie::fixed_to_float(z))),
                      true);
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
    fixie::set_matrix(fixie::matrix4::scale(fixie::vector3(fixie::fixed_to_float(x), fixie::fixed_to_float(y), fixie::fixed_to_float(z))), true);
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
    fixie::set_matrix(fixie::matrix4::translate(fixie::vector3(fixie::fixed_to_float(x), fixie::fixed_to_float(y), fixie::fixed_to_float(z))), true);
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
