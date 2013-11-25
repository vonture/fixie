#ifndef _FIXIE_CONTEXT_HPP_
#define _FIXIE_CONTEXT_HPP_

#include <memory>

#include "fixie_lib/exceptions.hpp"
#include "fixie_lib/state.hpp"
#include "fixie_lib/caps.hpp"
#include "fixie_lib/log.hpp"
#include "fixie_lib/noncopyable.hpp"

namespace fixie
{
    class context_impl : public noncopyable
    {
    public:
        virtual const fixie::caps& caps() = 0;
        virtual const std::string& renderer_desc() = 0;

        virtual void initialize_state(fixie::state& state) = 0;

        virtual std::unique_ptr<texture_impl> create_texture() = 0;
        virtual std::unique_ptr<framebuffer_impl> create_default_framebuffer() = 0;
        virtual std::unique_ptr<framebuffer_impl> create_framebuffer() = 0;
        virtual std::unique_ptr<buffer_impl> create_buffer() = 0;

        virtual void draw_arrays(const state& state, GLenum mode, GLint first, GLsizei count) = 0;
        virtual void draw_elements(const state& state, GLenum mode, GLsizei count, GLenum type, const GLvoid* indices) = 0;

        virtual void clear(const state& state, GLbitfield mask) = 0;
    };

    class context : public noncopyable
    {
    public:
        context(std::shared_ptr<context_impl> impl);

        GLuint create_texture();
        GLuint create_framebuffer();
        GLuint create_buffer();

        fixie::state& state();
        const fixie::state& state() const;

        const fixie::caps& caps() const;

        const std::string& version_string() const;
        const std::string& renderer_string() const;
        const std::string& vendor_string() const;
        const std::string& extension_string() const;

        void draw_arrays(GLenum mode, GLint first, GLsizei count);
        void draw_elements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices);

        void clear(GLbitfield mask);

        fixie::log& log();
        const fixie::log& log() const;

    private:
        std::shared_ptr<context_impl> _impl;
        fixie::state _state;

        std::string _version_string;
        std::string _renderer_string;
        std::string _vendor_string;
        std::string _extension_string;

        fixie::log _log;
    };

    std::shared_ptr<context> create_context();
    void destroy_context(context* ctx);

    std::shared_ptr<context> get_current_context();
    void set_current_context(context* ctx);

    void terminate();

    void log_gl_error(const gl_error& error);
    void log_context_error(const context_error& error);
    void log_message(GLenum source, GLenum type, GLuint id, GLenum severity, const std::string& msg);
}

#endif //_FIXIE_CONTEXT_HPP_
