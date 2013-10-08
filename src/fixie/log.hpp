#ifndef _LOG_HPP_
#define _LOG_HPP_

#include <functional>

#include "fixie/fixie.h"
#include "fixie/fixie_gl_types.h"

// todo: move these into a gl header
#define GL_DEBUG_CALLBACK_FUNCTION_ARB          0x8244
#define GL_DEBUG_CALLBACK_USER_PARAM_ARB        0x8245
#define GL_DEBUG_LOGGED_MESSAGES_ARB            0x9145
#define GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH_ARB 0x8243
#define GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB         0x8242
#define GL_DEBUG_SEVERITY_HIGH_ARB              0x9146
#define GL_DEBUG_SEVERITY_LOW_ARB               0x9148
#define GL_DEBUG_SEVERITY_MEDIUM_ARB            0x9147
#define GL_DEBUG_SOURCE_API_ARB                 0x8246
#define GL_DEBUG_SOURCE_APPLICATION_ARB         0x824A
#define GL_DEBUG_SOURCE_OTHER_ARB               0x824B
#define GL_DEBUG_SOURCE_SHADER_COMPILER_ARB     0x8248
#define GL_DEBUG_SOURCE_THIRD_PARTY_ARB         0x8249
#define GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB       0x8247
#define GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB   0x824D
#define GL_DEBUG_TYPE_ERROR_ARB                 0x824C
#define GL_DEBUG_TYPE_OTHER_ARB                 0x8251
#define GL_DEBUG_TYPE_PERFORMANCE_ARB           0x8250
#define GL_DEBUG_TYPE_PORTABILITY_ARB           0x824F
#define GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB    0x824E
#define GL_MAX_DEBUG_LOGGED_MESSAGES_ARB        0x9144
#define GL_MAX_DEBUG_MESSAGE_LENGTH_ARB         0x9143

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

#endif // _LOG_HPP_