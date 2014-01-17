#ifndef _FIXIE_LIB_DESKTOP_GL_EXCEPTIONS_HPP_
#define _FIXIE_LIB_DESKTOP_GL_EXCEPTIONS_HPP_

#include "fixie_lib/exceptions.hpp"

namespace fixie
{
    namespace desktop_gl_impl
    {
        class shader_error : public context_error
        {
        public:
            shader_error(const std::string& msg);
        };

        class null_shader : public shader_error
        {
        public:
            null_shader();
        };

        class compile_error : public shader_error
        {
        public:
            compile_error(const std::string& msg);
        };

        class link_error : public shader_error
        {
        public:
            link_error(const std::string& msg);
        };
    }
}

#endif // _FIXIE_LIB_DESKTOP_GL_EXCEPTIONS_HPP_
