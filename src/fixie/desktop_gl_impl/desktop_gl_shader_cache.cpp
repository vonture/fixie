#include "fixie/desktop_gl_impl/desktop_gl_shader_cache.hpp"

namespace fixie
{
    namespace desktop_gl_impl
    {
        shader_cache::shader_cache(std::shared_ptr<gl_functions> functions)
            : _functions(functions)
        {
        }
    }
}
