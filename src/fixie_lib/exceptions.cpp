#include "fixie_lib/exceptions.hpp"

#include "fixie/fixie_gl_es.h"

namespace fixie
{
    fixie_error::fixie_error(const std::string& msg)
        : std::runtime_error(msg)
        , _error_msg(msg)
    {
    }

    const std::string& fixie_error::error_msg() const
    {
        return _error_msg;
    }

    context_error::context_error(const std::string& msg)
        : fixie_error(msg)
    {
    }

    no_context_error::no_context_error()
        : context_error("no context exists.")
    {
    }

    state_error::state_error(const std::string& msg)
        : context_error(msg)
    {
    }

    gl_error::gl_error(GLenum error_code, const std::string& error_code_desc, const std::string& msg)
        : fixie_error(msg)
        , _error_code(error_code)
        , _error_code_description(error_code_desc)
    {
    }

    GLenum gl_error::error_code() const
    {
        return _error_code;
    }

    const std::string& gl_error::error_code_description() const
    {
        return _error_code_description;
    }

    invalid_enum_error::invalid_enum_error(const std::string& msg)
        : gl_error(GL_INVALID_ENUM, "invalid enum", msg)
    {
    }

    invalid_value_error::invalid_value_error(const std::string& msg)
        : gl_error(GL_INVALID_VALUE, "invalid value", msg)
    {
    }

    invalid_operation_error::invalid_operation_error(const std::string& msg)
        : gl_error(GL_INVALID_OPERATION, "invalid operation", msg)
    {
    }

    stack_overflow_error::stack_overflow_error(const std::string& msg)
        : gl_error(GL_STACK_OVERFLOW, "stack overflow", msg)
    {
    }

    stack_underflow_error::stack_underflow_error(const std::string& msg)
        : gl_error(GL_STACK_UNDERFLOW, "stack underflow", msg)
    {
    }

    out_of_memory_error::out_of_memory_error(const std::string& msg)
        : gl_error(GL_OUT_OF_MEMORY, "out of memory", msg)
    {
    }
}
