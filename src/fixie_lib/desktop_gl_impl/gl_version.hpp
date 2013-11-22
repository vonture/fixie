#ifndef _DESKTOP_GL_VERSION_HPP_
#define _DESKTOP_GL_VERSION_HPP_

#include "fixie/fixie_gl_types.h"

#include <string>

namespace fixie
{
    enum gl_context_type
    {
        open_gl,
        open_gl_es,
    };

    class gl_version
    {
    public:
        gl_version();
        gl_version(GLuint major, GLuint minor, gl_context_type type);
        explicit gl_version(const std::string& version_string);

        const GLuint& major() const;
        GLuint& major();

        const GLuint& minor() const;
        GLuint& minor();

        const gl_context_type& type() const;
        gl_context_type& type();

        std::string str() const;

    private:
        GLuint _major;
        GLuint _minor;
        gl_context_type _type;
    };

    extern const gl_version gl_3_0;
    extern const gl_version gl_4_3;
    extern const gl_version gl_es_2_0;
    extern const gl_version gl_es_3_0;

    bool operator==(const gl_version& a, const gl_version& b);
    bool operator!=(const gl_version& a, const gl_version& b);
    bool operator>=(const gl_version& a, const gl_version& b);
    bool operator>(const gl_version& a, const gl_version& b);
    bool operator<=(const gl_version& a, const gl_version& b);
    bool operator<(const gl_version& a, const gl_version& b);
}

#endif // _DESKTOP_GL_VERSION_HPP_
