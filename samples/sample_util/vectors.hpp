#ifndef _VECTORS_HPP_
#define _VECTORS_HPP_

#include <array>
#include <vector>

#include "fixie/fixie_gl_es.h"

namespace sample_util
{
    typedef std::array<float, 2> float2;
    typedef std::array<float, 3> float3;
    typedef std::array<float, 4> float4;

    template <typename type>
    static std::array<type, 2> construct_array(type a, type b);

    template <typename type>
    static std::array<type, 3> construct_array(type a, type b, type c);

    template <typename type>
    static std::array<type, 4> construct_array(type a, type b, type c, type d);

    template <typename element_type, size_t size>
    element_type& x(std::array<element_type, size>& vec);

    template <typename element_type, size_t size>
    const element_type& x(const std::array<element_type, size>& vec);

    template <typename element_type, size_t size>
    element_type& y(std::array<element_type, size>& vec);

    template <typename element_type, size_t size>
    const element_type& y(const std::array<element_type, size>& vec);

    template <typename element_type, size_t size>
    element_type& z(std::array<element_type, size>& vec);

    template <typename element_type, size_t size>
    const element_type& z(const std::array<element_type, size>& vec);

    template <typename element_type, size_t size>
    element_type& w(std::array<element_type, size>& vec);

    template <typename element_type, size_t size>
    const element_type& w(const std::array<element_type, size>& vec);

    template <typename element_type, size_t size>
    element_type& r(std::array<element_type, size>& vec);

    template <typename element_type, size_t size>
    const element_type& r(const std::array<element_type, size>& vec);

    template <typename element_type, size_t size>
    element_type& g(std::array<element_type, size>& vec);

    template <typename element_type, size_t size>
    const element_type& g(const std::array<element_type, size>& vec);

    template <typename element_type, size_t size>
    element_type& b(std::array<element_type, size>& vec);

    template <typename element_type, size_t size>
    const element_type& b(const std::array<element_type, size>& vec);

    template <typename element_type, size_t size>
    element_type& a(std::array<element_type, size>& vec);

    template <typename element_type, size_t size>
    const element_type& a(const std::array<element_type, size>& vec);

    template <typename element_type, size_t size>
    std::array<element_type, size> subtract(const std::array<element_type, size>& a, const std::array<element_type, size>& b);

    template <typename element_type, size_t size>
    element_type length(const std::array<element_type, size>& vec);

    template <typename element_type, size_t size>
    element_type length_squared(const std::array<element_type, size>& vec);

    template <typename element_type, size_t size>
    element_type distance(const std::array<element_type, size>& a, const std::array<element_type, size>& b);

    template <typename element_type, size_t size>
    element_type distance_squared(const std::array<element_type, size>& a, const std::array<element_type, size>& b);

    template <typename element_type, size_t size>
    std::array<element_type, size> max(const std::array<element_type, size>& a, const std::array<element_type, size>& b);

    template <typename element_type, size_t size, typename iterator_type>
    std::array<element_type, size> max(iterator_type first, iterator_type last);

    template <typename element_type, size_t size>
    std::array<element_type, size> min(const std::array<element_type, size>& a, const std::array<element_type, size>& b);

    template <typename element_type, size_t size, typename iterator_type>
    std::array<element_type, size> min(iterator_type first, iterator_type last);

    template <typename element_type, size_t size, typename iterator_type>
    void bounds(iterator_type first, iterator_type last, std::array<element_type, size>& min_bound, std::array<element_type, size>& max_bound);
}

#include "vectors.inl"

#endif // _VECTORS_HPP_
