#ifndef _FUNCTION_LOADER_HPP_
#define _FUNCTION_LOADER_HPP_

#include <functional>
#include <string>

#ifndef GL_APIENTRY
    #if defined(_WIN32)
        #define GL_APIENTRY __stdcall
    #else
        #define GL_APIENTRY
    #endif
#endif

#ifndef GL_APIENTRYP
    #define GL_APIENTRYP GL_APIENTRY*
#endif

namespace fixie
{
    template<typename T> std::function<T> load_gl_function(const std::string &name);
}

#include "function_loader.inl"

#endif // _FUNCTION_LOADER_HPP_
