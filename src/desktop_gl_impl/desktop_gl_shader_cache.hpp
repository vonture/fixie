#ifndef _DESKTOP_GL_SHADER_CACHE_HPP_
#define _DESKTOP_GL_SHADER_CACHE_HPP_

#include <memory>
#include "state.hpp"
#include "desktop_gl_impl/desktop_gl_functions.hpp"
#include "desktop_gl_impl/desktop_gl_shader.hpp"

namespace fixie
{
    namespace desktop_gl_impl
    {
        class shader_cache
        {
        public:
            shader_cache(std::shared_ptr<gl_functions> functions);

            std::shared_ptr<shader> get_shader(const state& state);

        private:
            std::shared_ptr<gl_functions> _functions;
        };
    }
}

#endif // _DESKTOP_GL_SHADER_GENERATOR_HPP_
