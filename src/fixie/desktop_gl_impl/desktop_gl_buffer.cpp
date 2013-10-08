#include "fixie/desktop_gl_impl/desktop_gl_buffer.hpp"

namespace fixie
{
    namespace desktop_gl_impl
    {
        buffer::buffer(std::shared_ptr<gl_functions> functions)
            : _functions(functions)
            , _id(0)
            , _type(0)
        {
            _functions->gl_gen_buffers()(1, &_id);
        }

        buffer::~buffer()
        {
            _functions->gl_delete_buffers()(1, &_id);
        }

        void buffer::set_type(GLenum type)
        {
            _type = type;
        }

        void buffer::set_data(GLsizeiptr size, const GLvoid* data, GLenum usage)
        {
            _functions->gl_bind_buffer()(_type, _id);
            _functions->gl_buffer_data()(_type, size, data, usage);
        }

        void buffer::set_sub_data(GLintptr offset, GLsizeiptr size, const GLvoid* data)
        {
            _functions->gl_bind_buffer()(_type, _id);
            _functions->gl_buffer_sub_data()(_type, offset, size, data);
        }
    }
}

