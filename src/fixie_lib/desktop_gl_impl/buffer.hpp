#ifndef _FIXIE_LIB_DESKTOP_GL_BUFFER_HPP_
#define _FIXIE_LIB_DESKTOP_GL_BUFFER_HPP_

#include "fixie_lib/buffer.hpp"
#include "fixie_lib/desktop_gl_impl/gl_functions.hpp"

namespace fixie
{
    namespace desktop_gl_impl
    {
        class buffer : public fixie::buffer_impl
        {
        public:
            explicit buffer(std::shared_ptr<const gl_functions> functions);
            virtual ~buffer();

            GLuint id() const;

            virtual void set_type(GLenum type) override;
            virtual void set_data(GLsizeiptr size, const GLvoid* data, GLenum usage) override;
            virtual void set_sub_data(GLintptr offset, GLsizeiptr size, const GLvoid* data) override;

        private:
            std::shared_ptr<const gl_functions> _functions;
            GLuint _id;
            GLenum _type;
        };
    }
}

#endif // _FIXIE_LIB_DESKTOP_GL_BUFFER_HPP_
