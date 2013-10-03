#ifndef _MATH_UTIL_HPP_
#define _MATH_UTIL_HPP_

namespace fixie
{
    template <typename T>
    T clamp(const T& val, const T& min, const T& max)
    {
        return (val < min) ? min : ((val > max) ? max : val);
    }

    template <typename T>
    T log2(T x)
    {
        T r = 0;
        while ((x >> r) > 1)
        {
            r++;
        }
        return r;
    }
}

#endif // _MATH_UTIL_HPP_
