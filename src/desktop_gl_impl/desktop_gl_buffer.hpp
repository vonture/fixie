#ifndef _DESKTOP_GL_BUFFER_HPP_
#define _DESKTOP_GL_BUFFER_HPP_

#include "buffer.hpp"

namespace fixie
{
    namespace desktop_gl_impl
    {
        class buffer : public fixie::buffer_impl
        {
        public:
            virtual void set_data(GLsizeiptr size, const GLvoid* data, GLenum usage) override;
            virtual void set_sub_data(GLintptr offset, GLsizeiptr size, const GLvoid* data) override;
        };
    }
}

#endif // _DESKTOP_GL_BUFFER_HPP_
