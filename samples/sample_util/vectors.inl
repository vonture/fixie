#include <assert.h>

namespace sample_util
{
    template <typename type>
    static std::array<type, 2> construct_array(type a, type b)
    {
        std::array<type, 2> result = { a, b, };
        return std::move(result);
    }

    template <typename type>
    static std::array<type, 3> construct_array(type a, type b, type c)
    {
        std::array<type, 3> result = { a, b, c, };
        return std::move(result);
    }

    template <typename type>
    static std::array<type, 4> construct_array(type a, type b, type c, type d)
    {
        std::array<type, 4> result = { a, b, c, d };
        return std::move(result);
    }

    template <typename element_type, size_t size>
    element_type& x(std::array<element_type, size>& vec)
    {
        static_assert(size > 0, "vector size must be at least 1");
        return vec[0];
    }

    template <typename element_type, size_t size>
    const element_type& x(const std::array<element_type, size>& vec)
    {
        static_assert(size > 0, "vector size must be at least 1");
        return vec[0];
    }

    template <typename element_type, size_t size>
    element_type& y(std::array<element_type, size>& vec)
    {
        static_assert(size > 1, "vector size must be at least 2");
        return vec[1];
    }

    template <typename element_type, size_t size>
    const element_type& y(const std::array<element_type, size>& vec)
    {
        static_assert(size > 1, "vector size must be at least 2");
        return vec[1];
    }

    template <typename element_type, size_t size>
    element_type& z(std::array<element_type, size>& vec)
    {
        static_assert(size > 2, "vector size must be at least 3");
        return vec[2];
    }

    template <typename element_type, size_t size>
    const element_type& z(const std::array<element_type, size>& vec)
    {
        static_assert(size > 2, "vector size must be at least 3");
        return vec[2];
    }

    template <typename element_type, size_t size>
    element_type& w(std::array<element_type, size>& vec)
    {
        static_assert(size > 3, "vector size must be at least 4");
        return vec[3];
    }

    template <typename element_type, size_t size>
    const element_type& w(const std::array<element_type, size>& vec)
    {
        static_assert(size > 3, "vector size must be at least 4");
        return vec[3];
    }

    template <typename element_type, size_t size>
    element_type& r(std::array<element_type, size>& vec)
    {
        static_assert(size > 0, "vector size must be at least 1");
        return vec[0];
    }

    template <typename element_type, size_t size>
    const element_type& r(const std::array<element_type, size>& vec)
    {
        static_assert(size > 0, "vector size must be at least 1");
        return vec[0];
    }

    template <typename element_type, size_t size>
    element_type& g(std::array<element_type, size>& vec)
    {
        static_assert(size > 1, "vector size must be at least 2");
        return vec[1];
    }

    template <typename element_type, size_t size>
    const element_type& g(const std::array<element_type, size>& vec)
    {
        static_assert(size > 1, "vector size must be at least 2");
        return vec[1];
    }

    template <typename element_type, size_t size>
    element_type& b(std::array<element_type, size>& vec)
    {
        static_assert(size > 2, "vector size must be at least 3");
        return vec[2];
    }

    template <typename element_type, size_t size>
    const element_type& b(const std::array<element_type, size>& vec)
    {
        static_assert(size > 2, "vector size must be at least 3");
        return vec[2];
    }

    template <typename element_type, size_t size>
    element_type& a(std::array<element_type, size>& vec)
    {
        static_assert(size > 3, "vector size must be at least 3");
        return vec[3];
    }

    template <typename element_type, size_t size>
    const element_type& a(const std::array<element_type, size>& vec)
    {
        static_assert(size > 3, "vector size must be at least 3");
        return vec[3];
    }

    template <typename element_type, size_t size>
    std::array<element_type, size> subtract(const std::array<element_type, size>& a, const std::array<element_type, size>& b)
    {
        std::array<element_type, size> output;
        for (size_t i = 0; i < size; ++i)
        {
            output[i] = a[i] - b[i];
        }
        return std::move(output);
    }

    template <typename element_type, size_t size>
    element_type length(const std::array<element_type, size>& vec)
    {
        return std::sqrt(length_squared(vec));
    }

    template <typename element_type, size_t size>
    element_type length_squared(const std::array<element_type, size>& vec)
    {
        element_type sum = element_type(0);
        for (size_t i = 0; i < size; ++i)
        {
            sum += (vec[i] * vec[i]);
        }
        return sum;
    }

    template <typename element_type, size_t size>
    element_type distance(const std::array<element_type, size>& a, const std::array<element_type, size>& b)
    {
        return length(subtract(a, b));
    }

    template <typename element_type, size_t size>
    element_type distance_squared(const std::array<element_type, size>& a, const std::array<element_type, size>& b)
    {
        return length_squared(subtract(a, b));
    }

    template <typename element_type, size_t size>
    std::array<element_type, size> max(const std::array<element_type, size>& a, const std::array<element_type, size>& b)
    {
        std::array<element_type, size> output;
        for (size_t i = 0; i < size; ++i)
        {
            output[i] = std::max(a[i], b[i]);
        }
        return std::move(output);
    }

    template <typename element_type, size_t size, typename iterator_type>
    std::array<element_type, size> max(iterator_type first, iterator_type last)
    {
        std::array<element_type, size> output;
        output.assign(std::numeric_limits<element_type>::min());
        for (iterator_type i = first; i != last; ++i)
        {
            output = max(output, *i);
        }
        return std::move(output);
    }

    template <typename element_type, size_t size>
    std::array<element_type, size> min(const std::array<element_type, size>& a, const std::array<element_type, size>& b)
    {
        std::array<element_type, size> output;
        for (size_t i = 0; i < size; ++i)
        {
            output[i] = std::min(a[i], b[i]);
        }
        return std::move(output);
    }

    template <typename element_type, size_t size, typename iterator_type>
    std::array<element_type, size> min(iterator_type first, iterator_type last)
    {
        std::array<element_type, size> output;
        output.assign(std::numeric_limits<element_type>::max());
        for (iterator_type i = first; i != last; ++i)
        {
            output = min(output, *i);
        }
        return std::move(output);
    }

    template <typename element_type, size_t size, typename iterator_type>
    void bounds(iterator_type first, iterator_type last, std::array<element_type, size>& min_bound, std::array<element_type, size>& max_bound)
    {
        min_bound.assign(std::numeric_limits<element_type>::max());
        max_bound.assign(std::numeric_limits<element_type>::min());
        for (iterator_type i = first; i != last; ++i)
        {
            min_bound = min(min_bound, *i);
            max_bound = max(max_bound, *i);
        }
    }
}
