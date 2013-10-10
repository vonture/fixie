#ifndef _DESKTOP_GL_SHADER_HPP_
#define _DESKTOP_GL_SHADER_HPP_

#include <memory>
#include "fixie/desktop_gl_impl/shader_info.hpp"
#include "fixie/desktop_gl_impl/gl_functions.hpp"

namespace fixie
{
    namespace desktop_gl_impl
    {
        class shader
        {
        public:
            shader(const shader_info& info, std::shared_ptr<gl_functions> functions);

        private:
            std::shared_ptr<gl_functions> _functions;
        };
    }
}

#endif // _DESKTOP_GL_SHADER_HPP_
