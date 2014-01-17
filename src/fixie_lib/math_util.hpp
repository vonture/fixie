#ifndef _FIXIE_LIB_MATH_UTIL_HPP_
#define _FIXIE_LIB_MATH_UTIL_HPP_

namespace fixie
{
    template <typename value_type>
    value_type clamp(const value_type& val, const value_type& min, const value_type& max);

    template <typename number_type>
    number_type log_two(const number_type& x);

    template <typename number_type>
    bool is_power_of_two(const number_type& number);
}

#include "fixie_lib/math_util.inl"

#endif // _FIXIE_LIB_MATH_UTIL_HPP_
