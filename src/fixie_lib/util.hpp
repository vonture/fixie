#ifndef _UTIL_HPP_
#define _UTIL_HPP_

#include <string>

namespace fixie
{
    std::string format(const char* fmt, ...);
    const char* make_static(const std::string& str);

    template <typename output_iterator>
    void split(const std::string& input, char delim, output_iterator output);

    template <class T>
    void hash_combine(std::size_t& seed, const T& v);
}

#include "util.inl"

#endif // _UTIL_HPP_
