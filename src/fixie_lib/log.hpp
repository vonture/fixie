#ifndef _FIXIE_LIB_LOG_HPP_
#define _FIXIE_LIB_LOG_HPP_

#include <functional>

#include "fixie/fixie.h"
#include "fixie/fixie_ext.h"
#include "fixie/fixie_gl_types.h"

namespace fixie
{
    typedef std::function<void FIXIE_APIENTRY (GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const GLvoid* user_param)> debug_msg_callback;

    class log
    {
    public:
        log();

        debug_msg_callback& callback();
        const debug_msg_callback& callback() const;

        GLvoid*& user_param();
        const GLvoid* user_param() const;

    private:
        debug_msg_callback _callback;
        GLvoid* _user_param;
    };

    debug_msg_callback get_default_debug_msg_callback();
}

#endif // _FIXIE_LIB_LOG_HPP_
