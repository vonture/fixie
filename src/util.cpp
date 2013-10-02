#include "util.hpp"

#include <stdarg.h>
#include <vector>

namespace fixie
{
    std::string format(const char* fmt, ...)
    {
        va_list s;

        va_start(s, fmt);
        int len = vsnprintf(NULL, 0, fmt, s);
        va_end(s);

        std::vector<char> buf(len + 1);

        va_start(s, fmt);
        vsnprintf(buf.data(), buf.size(), fmt, s);
        va_end(s);

        buf[buf.size() - 1] = '\0';

        return std::string(buf.data());
    }
}
