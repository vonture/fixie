#include "fixie_lib/desktop_gl_impl/exceptions.hpp"

namespace fixie
{
    namespace desktop_gl_impl
    {
        shader_error::shader_error(const std::string& msg)
            : context_error(msg)
        {
        }

        null_shader::null_shader()
            : shader_error("null shader.")
        {
        }

        compile_error::compile_error(const std::string& msg)
            : shader_error(msg)
        {
        }

        link_error::link_error(const std::string& msg)
            : shader_error(msg)
        {
        }
    }
}
