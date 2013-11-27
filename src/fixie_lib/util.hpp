#ifndef _UTIL_HPP_
#define _UTIL_HPP_

#include <string>

namespace fixie
{
    template <typename char_type>
    std::basic_string<char_type> format(const char_type* fmt, ...);

    template <typename string_type>
    typename string_type::const_pointer make_static(const string_type& str);

    template <typename output_iterator>
    void split(const std::string& input, char delim, output_iterator output);

    template <typename iterator_type, typename func_type>
    func_type for_each_n(iterator_type first, iterator_type last, func_type func);

    template <class hash_type>
    void hash_combine(std::size_t& seed, const hash_type& v);
}

#include "util.inl"

#endif // _UTIL_HPP_
