#ifndef _FIXIE_EXCEPTIONS_HPP_
#define _FIXIE_EXCEPTIONS_HPP_

namespace fixie
{
    void handle_entry_point_exception();

    template <typename return_type>
    return_type handle_entry_point_exception(const return_type& return_value);
}

#include "fixie/exceptions.inl"

#endif // _FIXIE_EXCEPTIONS_HPP_
