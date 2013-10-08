#include "fixie/util.hpp"

#include <stdarg.h>
#include <vector>
#include <set>

namespace fixie
{
    std::string format(const char* fmt, ...)
    {
        va_list s;

        va_start(s, fmt);
        int len = vsnprintf(nullptr, 0, fmt, s);
        va_end(s);

        std::vector<char> buf(len + 1);

        va_start(s, fmt);
        vsnprintf(buf.data(), buf.size(), fmt, s);
        va_end(s);

        buf[buf.size() - 1] = '\0';

        return std::string(buf.data());
    }

    const char* make_static(const std::string& str)
    {
        static std::set<std::string> static_strings;
        auto iter = static_strings.find(str);
        if (iter != static_strings.end())
        {
            return iter->c_str();
        }
        else
        {
            return static_strings.insert(str).first->c_str();
        }
    }
}
