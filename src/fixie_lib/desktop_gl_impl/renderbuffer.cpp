#include "fixie_lib/desktop_gl_impl/renderbuffer.hpp"

namespace fixie
{
    namespace desktop_gl_impl
    {
        #define GL_RENDERBUFFER 0x8D41
        #define GL_RENDERBUFFER_RED_SIZE 0x8D50
        #define GL_RENDERBUFFER_GREEN_SIZE 0x8D51
        #define GL_RENDERBUFFER_BLUE_SIZE 0x8D52
        #define GL_RENDERBUFFER_ALPHA_SIZE 0x8D53
        #define GL_RENDERBUFFER_DEPTH_SIZE 0x8D54
        #define GL_RENDERBUFFER_STENCIL_SIZE 0x8D55

        renderbuffer::renderbuffer(std::shared_ptr<const gl_functions> functions)
            : _functions(functions)
            , _id(0)
        {
            gl_call(_functions, gen_renderbuffers, 1, &_id);
        }

        renderbuffer::~renderbuffer()
        {
            gl_call_nothrow(_functions, delete_renderbuffers, 1, &_id);
        }

        GLuint renderbuffer::id() const
        {
            return _id;
        }

        GLsizei renderbuffer::red_size() const
        {
            gl_call(_functions, bind_renderbuffer, GL_RENDERBUFFER, _id);

            GLint size;
            gl_call(_functions, get_renderbuffer_parameter_iv, GL_RENDERBUFFER, GL_RENDERBUFFER_RED_SIZE, &size);
            return size;
        }

        GLsizei renderbuffer::green_size() const
        {
            gl_call(_functions, bind_renderbuffer, GL_RENDERBUFFER, _id);

            GLint size;
            gl_call(_functions, get_renderbuffer_parameter_iv, GL_RENDERBUFFER, GL_RENDERBUFFER_GREEN_SIZE, &size);
            return size;
        }

        GLsizei renderbuffer::blue_size() const
        {
            gl_call(_functions, bind_renderbuffer, GL_RENDERBUFFER, _id);

            GLint size;
            gl_call(_functions, get_renderbuffer_parameter_iv, GL_RENDERBUFFER, GL_RENDERBUFFER_BLUE_SIZE, &size);
            return size;
        }

        GLsizei renderbuffer::alpha_size() const
        {
            gl_call(_functions, bind_renderbuffer, GL_RENDERBUFFER, _id);

            GLint size;
            gl_call(_functions, get_renderbuffer_parameter_iv, GL_RENDERBUFFER, GL_RENDERBUFFER_ALPHA_SIZE, &size);
            return size;
        }

        GLsizei renderbuffer::depth_size() const
        {
            gl_call(_functions, bind_renderbuffer, GL_RENDERBUFFER, _id);

            GLint size;
            gl_call(_functions, get_renderbuffer_parameter_iv, GL_RENDERBUFFER, GL_RENDERBUFFER_DEPTH_SIZE, &size);
            return size;
        }

        GLsizei renderbuffer::stencil_size() const
        {
            gl_call(_functions, bind_renderbuffer, GL_RENDERBUFFER, _id);

            GLint size;
            gl_call(_functions, get_renderbuffer_parameter_iv, GL_RENDERBUFFER, GL_RENDERBUFFER_STENCIL_SIZE, &size);
            return size;
        }

        void renderbuffer::set_storage(GLenum target, GLenum internal_format, GLsizei width, GLsizei height)
        {
            gl_call(_functions, bind_renderbuffer, GL_RENDERBUFFER, _id);
            gl_call(_functions, renderbuffer_storage, target, internal_format, width, height);
        }

        void renderbuffer::set_storage_multisample(GLenum target, GLsizei samples, GLenum internal_format, GLsizei width, GLsizei height)
        {
            gl_call(_functions, bind_renderbuffer, GL_RENDERBUFFER, _id);
            gl_call(_functions, renderbuffer_storage_multisample, target, samples, internal_format, width, height);
        }
    }
}
