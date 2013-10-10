#include <iostream>
#include <sstream>

namespace fixie
{
    template <typename output_iterator>
    void split(const std::string& input, char delim, output_iterator output)
    {
        std::stringstream stream(input);
        std::string item;
        while (std::getline(stream, item, delim))
        {
            *output = item;
            ++output;
        }
    }

    template <class T>
    void hash_combine(std::size_t& seed, const T& v)
    {
        std::hash<T> hasher;
        seed ^= hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
    }
}
