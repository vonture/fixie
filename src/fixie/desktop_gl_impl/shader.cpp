#include "fixie/desktop_gl_impl/shader.hpp"

namespace fixie
{
    namespace desktop_gl_impl
    {
        shader::shader(const shader_info& info, std::shared_ptr<gl_functions> functions)
            : _functions(functions)
        {
        }
    }
}
