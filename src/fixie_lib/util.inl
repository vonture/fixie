#include <stdarg.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <set>

namespace fixie
{
    namespace priv
    {
        template <typename char_type>
        struct format_func
        {
            int operator()(char_type* dest, size_t count, const char_type* format, va_list args) { /*static_assert(false, "no template specialization for format func.");*/ return 0; }
        };

        template <>
        struct format_func<char>
        {
            int operator()(char* dest, size_t count, const char* format, va_list args) { return vsnprintf(dest, count, format, args); }
        };

        template <>
        struct format_func<wchar_t>
        {
            int operator()(wchar_t* dest, size_t count, const wchar_t* format, va_list args) { return vswprintf(dest, count, format, args); }
        };
    }

    template <typename char_type>
    std::basic_string<char_type> format(const char_type* fmt, ...)
    {
        priv::format_func<char_type> formatter;

        va_list s;
        va_start(s, fmt);
        int len = formatter(nullptr, 0, fmt, s);
        va_end(s);

        std::vector<char_type> buf(len + 1);

        va_start(s, fmt);
        formatter(buf.data(), buf.size(), fmt, s);
        va_end(s);

        buf.back() = 0;

        return std::basic_string<char_type>(buf.data());
    }

    template <typename string_type>
    typename string_type::const_pointer make_static(const string_type& str)
    {
        static std::set<string_type> static_strings;
        auto iter = static_strings.find(str);
        if (iter != end(static_strings))
        {
            return iter->c_str();
        }
        else
        {
            return static_strings.insert(str).first->c_str();
        }
    }

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

    template <typename iterator_type, typename func_type>
    func_type for_each_n(iterator_type first, iterator_type last, func_type func)
    {
        for (iterator_type i = first; i != last; ++i)
        {
            func(i);
        }

        return func;
    }

    template <class iterator_type, typename predicate>
    bool equal_n(iterator_type first, iterator_type last, predicate pred)
    {
        for (iterator_type i = first; i != last; ++i)
        {
            if (!pred(i))
            {
                return false;
            }
        }
        return true;
    }

    template <class hash_type>
    void hash_combine(std::size_t& seed, const hash_type& v)
    {
        std::hash<hash_type> hasher;
        seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

    template <typename iterator_type, typename second_type>
    iterator_type reverse_find(iterator_type first, iterator_type last, const second_type& item)
    {
        for (iterator_type i = first; i != last; ++i)
        {
            if (i->second == item)
            {
                return i;
            }
        }

        return last;
    }

    template <typename dest_type, typename source_type>
    dest_type bit_cast(const source_type& source)
    {
        dest_type dest;
        memcpy(&dest, &source, std::min(sizeof(dest_type), sizeof(source_type)));
        return dest;
    }
}
