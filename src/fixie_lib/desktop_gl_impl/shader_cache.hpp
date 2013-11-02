#ifndef _DESKTOP_GL_SHADER_CACHE_HPP_
#define _DESKTOP_GL_SHADER_CACHE_HPP_

#include <memory>
#include "fixie_lib/state.hpp"
#include "fixie_lib/caps.hpp"
#include "fixie_lib/desktop_gl_impl/gl_functions.hpp"
#include "fixie_lib/desktop_gl_impl/shader.hpp"
#include "fixie_lib/desktop_gl_impl/shader_info.hpp"

namespace fixie
{
    namespace desktop_gl_impl
    {
        class shader_cache
        {
        public:
            shader_cache(std::shared_ptr<const gl_functions> functions);

            std::weak_ptr<shader> get_shader(const state& state, const caps& caps);

        private:
            std::shared_ptr<const gl_functions> _functions;
            std::unordered_map< shader_info, std::shared_ptr<shader> > _shaders;
        };
    }
}

#endif // _DESKTOP_GL_SHADER_GENERATOR_HPP_
