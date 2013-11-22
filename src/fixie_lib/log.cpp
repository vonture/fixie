#include "fixie_lib/log.hpp"

#include <iostream>
#include <string>

namespace fixie
{
    log::log()
        : _callback(get_default_debug_msg_callback())
        , _user_param(nullptr)
    {
    }

    debug_msg_callback& log::callback()
    {
        return _callback;
    }

    const debug_msg_callback& log::callback() const
    {
        return _callback;
    }

    GLvoid*& log::user_param()
    {
        return _user_param;
    }

    const GLvoid* log::user_param() const
    {
        return _user_param;
    }

    static void FIXIE_APIENTRY log_to_stream(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message,
                                             const GLvoid* user_param)
    {
        std::string source_text;
        switch (source)
        {
        case GL_DEBUG_SOURCE_API:             source_text = "api";             break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   source_text = "windows";         break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: source_text = "shader compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     source_text = "third Party";     break;
        case GL_DEBUG_SOURCE_APPLICATION:     source_text = "application";     break;
        case GL_DEBUG_SOURCE_OTHER:           source_text = "other";           break;
        default:                              source_text = "unknown";         break;
        }

        std::string type_text;
        switch (type)
        {
        case GL_DEBUG_TYPE_ERROR:               type_text = "error";               break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: type_text = "deprecated behavior"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  type_text = "undefined behavior";  break;
        case GL_DEBUG_TYPE_PORTABILITY:         type_text = "portability";         break;
        case GL_DEBUG_TYPE_PERFORMANCE:         type_text = "performance";         break;
        case GL_DEBUG_TYPE_OTHER:               type_text = "other";               break;
        default:                                type_text = "unknown";             break;
        }
        std::ostream& output_stream = (type == GL_DEBUG_TYPE_ERROR) ? std::cerr : std::clog;

        std::string severity_text;
        switch (severity)
        {
        case GL_DEBUG_SEVERITY_HIGH:   severity_text = "high";    break;
        case GL_DEBUG_SEVERITY_MEDIUM: severity_text = "medium";  break;
        case GL_DEBUG_SEVERITY_LOW:    severity_text = "low";     break;
        default:                       severity_text = "unknown"; break;
        }

        output_stream << "fixie debug message: " << std::endl;
        output_stream << "    source: " << source_text << std::endl;
        output_stream << "    type: " << type_text << std::endl;
        output_stream << "    severity: " << severity_text << std::endl;
        output_stream << "    message: " << message << std::endl;
        output_stream << std::endl;
    }

    debug_msg_callback get_default_debug_msg_callback()
    {
        return log_to_stream;
    }
}
