#ifndef _FUNCTION_LOADER_HPP
#define _FUNCTION_LOADER_HPP

#include <functional>
#include <string>

namespace fixie
{
    template<typename T> std::function<T> load_gl_function(const std::string &name);
}

#include "function_loader.inl"

#endif // _FUNCTION_LOADER_HPP
