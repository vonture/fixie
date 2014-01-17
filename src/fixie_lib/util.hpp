#ifndef _FIXIE_LIB_UTIL_HPP_
#define _FIXIE_LIB_UTIL_HPP_

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

    template <typename iterator_type, typename predicate>
    bool equal_n(iterator_type first, iterator_type last, predicate pred);

    template <typename hash_type>
    void hash_combine(std::size_t& seed, const hash_type& v);

    template <typename iterator_type, typename second_type>
    iterator_type reverse_find(iterator_type first, iterator_type last, const second_type& item);

    template <typename dest_type, typename source_type>
    dest_type bit_cast(const source_type& source);
}

#include "util.inl"

#endif // _FIXIE_LIB_UTIL_HPP_
