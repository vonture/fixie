#include "fixie_lib/desktop_gl_impl/shader.hpp"

#include "fixie_lib/util.hpp"
#include <sstream>

namespace fixie
{
    namespace desktop_gl_impl
    {
        shader::shader(const shader_info& info, std::shared_ptr<const gl_functions> functions)
            : _functions(functions)
        {
        }

        void shader::sync_state(const state& state)
        {
        }
    }
}
