#include "fixie_lib/desktop_gl_impl/renderbuffer.hpp"

namespace fixie
{
    namespace desktop_gl_impl
    {
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

        void renderbuffer::set_storage(GLenum target, GLenum internal_format, GLsizei width, GLsizei height)
        {
            gl_call(_functions, renderbuffer_storage, target, internal_format, width, height);
        }

        void renderbuffer::set_storage_multisample(GLenum target, GLsizei samples, GLenum internal_format, GLsizei width, GLsizei height)
        {
            gl_call(_functions, renderbuffer_storage_multisample, target, samples, internal_format, width, height);
        }
    }
}
