#ifndef _DESKTOP_GL_BUFFER_HPP_
#define _DESKTOP_GL_BUFFER_HPP_

#include "buffer.hpp"
#include "desktop_gl_impl/desktop_gl_functions.hpp"

namespace fixie
{
    namespace desktop_gl_impl
    {
        class buffer : public fixie::buffer_impl
        {
        public:
            buffer(std::shared_ptr<gl_functions> functions);
            ~buffer();

            virtual void set_type(GLenum type) override;
            virtual void set_data(GLsizeiptr size, const GLvoid* data, GLenum usage) override;
            virtual void set_sub_data(GLintptr offset, GLsizeiptr size, const GLvoid* data) override;

        private:
            std::shared_ptr<gl_functions> _functions;
            GLuint _id;
            GLenum _type;
        };
    }
}

#endif // _DESKTOP_GL_BUFFER_HPP_
