#include "fixie_lib/desktop_gl_impl/gl_version.hpp"

#include "fixie_lib/util.hpp"

#include <regex>

namespace fixie
{
    gl_version::gl_version()
        : _major(0)
        , _minor(0)
        , _type(open_gl)
    {
    }

    gl_version::gl_version(const std::string& version_string)
        : _major(0)
        , _minor(0)
        , _type(open_gl)
    {
        const std::regex version_regex("(OpenGL ES )?(\\d)\\.(\\d)\\.*");

        std::smatch match;
        if (std::regex_search(version_string.begin(), version_string.end(), match, version_regex))
        {
            _major = static_cast<GLuint>(std::stoul(match[2].str()));
            _minor = static_cast<GLuint>(std::stoul(match[3].str()));
            _type = match[1].matched ? open_gl_es : open_gl;
        }
    }

    gl_version::gl_version(GLuint major, GLuint minor, gl_context_type type)
        : _major(major)
        , _minor(minor)
        , _type(type)
    {
    }

    const GLuint& gl_version::major() const
    {
        return _major;
    }

    GLuint& gl_version::major()
    {
        return _major;
    }

    const GLuint& gl_version::minor() const
    {
        return _minor;
    }

    GLuint& gl_version::minor()
    {
        return _minor;
    }

    const gl_context_type& gl_version::type() const
    {
        return _type;
    }

    gl_context_type& gl_version::type()
    {
        return _type;
    }

    std::string gl_version::str() const
    {
        return format("%s%u.%u", (_type == open_gl_es) ? "ES " : "", _major, _minor);
    }

    const gl_version gl_3_0 = gl_version(3, 0, open_gl);
    const gl_version gl_4_3 = gl_version(4, 3, open_gl);
    const gl_version gl_es_3_0 = gl_version(3, 0, open_gl_es);
    const gl_version gl_es_2_0 = gl_version(2, 0, open_gl_es);

    bool operator==(const gl_version& a, const gl_version& b)
    {
        return a.major() == b.major() && a.minor() == b.minor() && a.type() == b.type();
    }

    bool operator!=(const gl_version& a, const gl_version& b)
    {
        return !(a == b);
    }

    bool operator>=(const gl_version& a, const gl_version& b)
    {
        return a.type() == b.type() && ((a.major() != b.major()) ? (a.major() >= b.major()) : (a.minor() >= b.minor()));
    }

    bool operator>(const gl_version& a, const gl_version& b)
    {
        return a.type() == b.type() && ((a.major() != b.major()) ? (a.major() > b.major()) : (a.minor() > b.minor()));
    }

    bool operator<=(const gl_version& a, const gl_version& b)
    {
        return a.type() == b.type() && ((a.major() != b.major()) ? (a.major() <= b.major()) : (a.minor() <= b.minor()));
    }

    bool operator<(const gl_version& a, const gl_version& b)
    {
        return a.type() == b.type() && ((a.major() != b.major()) ? (a.major() < b.major()) : (a.minor() < b.minor()));
    }
}
