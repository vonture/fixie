#include "exceptions.hpp"

#include "fixie_gl_es.h"

namespace fixie
{
    context_error::context_error(const std::string& msg)
        : std::runtime_error(msg)
    {
    }

    no_context_error::no_context_error()
        : context_error("no context exists.")
    {
    }

    gl_error::gl_error(GLenum error_code, const std::string& msg)
        : std::runtime_error(msg)
        , _error_code(error_code)
    {
    }

    GLenum gl_error::error_code() const
    {
        return _error_code;
    }

    invalid_enum_error::invalid_enum_error(const std::string& msg)
        : gl_error(GL_INVALID_ENUM, msg)
    {
    }

    invalid_value_error::invalid_value_error(const std::string& msg)
        : gl_error(GL_INVALID_VALUE, msg)
    {
    }

    invalid_operation_error::invalid_operation_error(const std::string& msg)
        : gl_error(GL_INVALID_OPERATION, msg)
    {
    }

    stack_overflow_error::stack_overflow_error(const std::string& msg)
        : gl_error(GL_STACK_OVERFLOW, msg)
    {
    }

    stack_underflow_error::stack_underflow_error(const std::string& msg)
        : gl_error(GL_STACK_UNDERFLOW, msg)
    {
    }

    out_of_memory_error::out_of_memory_error(const std::string& msg)
        : gl_error(GL_OUT_OF_MEMORY, msg)
    {
    }
}
