#ifndef _NULL_BUFFER_HPP_
#define _NULL_BUFFER_HPP_

#include "buffer.hpp"

namespace fixie
{
    namespace null_impl
    {
        class buffer : public fixie::buffer_impl
        {
        public:
            virtual void set_type(GLenum type) override;
            virtual void set_data(GLsizeiptr size, const GLvoid* data, GLenum usage) override;
            virtual void set_sub_data(GLintptr offset, GLsizeiptr size, const GLvoid* data) override;
        };
    }
}

#endif // _NULL_BUFFER_HPP_
