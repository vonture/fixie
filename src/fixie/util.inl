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
}
