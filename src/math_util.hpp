#ifndef _MATH_UTIL_HPP_
#define _MATH_UTIL_HPP_

namespace fixie
{
    template <typename T>
    T clamp(const T& val, const T& min, const T& max)
    {
        return (val < min) ? min : (val > max) ? max : val;
    }
}

#endif // MATH_UTIL
