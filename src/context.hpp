#ifndef _FIXIE_CONTEXT_HPP_
#define _FIXIE_CONTEXT_HPP_

#include <memory>

#include "exceptions.hpp"
#include "state.hpp"
#include "log.hpp"

namespace fixie
{
    class context_impl
    {
    public:
        virtual std::shared_ptr<texture_impl> create_texture() = 0;
        virtual std::shared_ptr<buffer_impl> create_buffer() = 0;

        virtual void draw_arrays(const state& state, GLenum mode, GLint first, GLsizei count) = 0;
        virtual void draw_elements(const state& state, GLenum mode, GLsizei count, GLenum type, GLvoid* indices) = 0;

        virtual void clear(const state& state, GLbitfield mask) = 0;
    };

    class context
    {
    public:
        context(std::shared_ptr<context_impl> impl);

        GLuint create_texture();
        GLuint create_buffer();

        fixie::state& state();
        const fixie::state& state() const;

        void draw_arrays(GLenum mode, GLint first, GLsizei count);
        void draw_elements(GLenum mode, GLsizei count, GLenum type, GLvoid* indices);

        void clear(GLbitfield mask);

        fixie::log& log();
        const fixie::log& log() const;

    private:
        std::shared_ptr<context_impl> _impl;
        fixie::state _state;

        fixie::log _log;
    };

    std::shared_ptr<context> create_context();
    void destroy_context(context* ctx);

    std::shared_ptr<context> get_current_context();
    void set_current_context(context* ctx);

    void log_gl_error(const gl_error& error);
    void log_context_error(const context_error& error);
    void log_message(GLenum source, GLenum type, GLuint id, GLenum severity, const std::string& msg);
}

#endif //_FIXIE_CONTEXT_HPP_
