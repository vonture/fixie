#include "fixie_lib/desktop_gl_impl/buffer.hpp"

namespace fixie
{
    namespace desktop_gl_impl
    {
        buffer::buffer(std::shared_ptr<const gl_functions> functions)
            : _functions(functions)
            , _id(0)
            , _type(0)
        {
            gl_call(_functions, gen_buffers, 1, &_id);
        }

        buffer::~buffer()
        {
            gl_call_nothrow(_functions, delete_buffers, 1, &_id);
        }

        GLuint buffer::id() const
        {
            return _id;
        }

        void buffer::set_type(GLenum type)
        {
            _type = type;
        }

        void buffer::set_data(GLsizeiptr size, const GLvoid* data, GLenum usage)
        {
            gl_call(_functions, bind_buffer, _type, _id);
            gl_call(_functions, buffer_data, _type, size, data, usage);
        }

        void buffer::set_sub_data(GLintptr offset, GLsizeiptr size, const GLvoid* data)
        {
            gl_call(_functions, bind_buffer, _type, _id);
            gl_call(_functions, buffer_sub_data, _type, offset, size, data);
        }
    }
}

