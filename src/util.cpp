#include "util.hpp"

#include <stdarg.h>
#include <vector>

namespace fixie
{
    std::string format(const std::string& fmt, ...)
    {
        va_list s;

        va_start(s, fmt);
        int len = vsnprintf(NULL, 0, fmt.c_str(), s);
        va_end(s);

        std::vector<char> buf(len + 1);

        va_start(s, fmt); 
        vsnprintf(buf.data(), buf.size(), fmt.c_str(), s);
        va_end(s);

        buf[buf.size() - 1] = '\0';

        return std::string(buf.data());
    }
}
