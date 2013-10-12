#include "fixie_lib/desktop_gl_impl/shader_cache.hpp"

namespace fixie
{
    namespace desktop_gl_impl
    {
        shader_cache::shader_cache(std::shared_ptr<const gl_functions> functions)
            : _functions(functions)
        {
        }

        std::shared_ptr<shader> shader_cache::get_shader(const state& state, const caps& caps)
        {
            shader_info key(state, caps);
            auto iter = _shaders.find(key);
            if (iter != end(_shaders))
            {
                return iter->second;
            }
            else
            {
                std::shared_ptr<shader> generated_shader = std::make_shared<shader>(key, _functions);
                _shaders.insert(std::make_pair(key, generated_shader));
                return generated_shader;
            }
        }
    }
}
