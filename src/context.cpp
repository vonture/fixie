#include "context.hpp"
#include "exceptions.hpp"
#include "fixie_gl_es.h"
#include "debug.hpp"
#include "util.hpp"

#include <set>
#include <algorithm>
#include <functional>

namespace fixie
{
    context::context(std::shared_ptr<context_impl> impl)
        : _impl(impl)
        , _state(impl->caps())
    {
        _impl->initialize_state(_state);
        _version_string = format("OpenGL ES-%s %u.%u", "CM", 1, 1);
        _renderer_string = format("fixie (%s)", _impl->renderer_desc().c_str());
        _vendor_string = format("vonture");
        _extension_string = format("");
    }

    GLuint context::create_texture()
    {
        std::shared_ptr<texture_impl> impl = _impl->create_texture();
        std::shared_ptr<fixie::texture> texture = std::make_shared<fixie::texture>(impl);
        return _state.insert_texture(texture);
    }

    GLuint context::create_buffer()
    {
        std::shared_ptr<buffer_impl> impl = _impl->create_buffer();
        std::shared_ptr<fixie::buffer> buffer = std::make_shared<fixie::buffer>(impl);
        return _state.insert_buffer(buffer);
    }

    fixie::state& context::state()
    {
        return _state;
    }

    const fixie::state& context::state() const
    {
        return _state;
    }

    const fixie::caps& context::caps() const
    {
        return _impl->caps();
    }

    const std::string& context::version_string() const
    {
        return _version_string;
    }

    const std::string& context::renderer_string() const
    {
        return _renderer_string;
    }

    const std::string& context::vendor_string() const
    {
        return _vendor_string;
    }

    const std::string& context::extension_string() const
    {
        return _extension_string;
    }

    fixie::log& context::log()
    {
        return _log;
    }

    const fixie::log& context::log() const
    {
        return _log;
    }

    void context::draw_arrays(GLenum mode, GLint first, GLsizei count)
    {
        _impl->draw_arrays(_state, mode, first, count);
    }

    void context::draw_elements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices)
    {
        _impl->draw_elements(_state, mode, count, type, indices);
    }

    void context::clear(GLbitfield mask)
    {
        _impl->clear(_state, mask);
    }
}

#include "null_impl/null_context.hpp"
#include "desktop_gl_impl/desktop_gl_context.hpp"

namespace fixie
{
    std::shared_ptr<context_impl> current_context_impl;
    std::shared_ptr<context> current_context;
    std::set< std::shared_ptr<context> > all_contexts;

    std::shared_ptr<context> create_context()
    {
        if (!current_context_impl)
        {
            current_context_impl = std::make_shared<desktop_gl_impl::context>();
        }

        std::shared_ptr<context> ctx = std::make_shared<context>(current_context_impl);
        all_contexts.insert(ctx);
        return ctx;
    }

    static bool context_equals(context* a, std::shared_ptr<context> b)
    {
        return a == b.get();
    }

    void destroy_context(context* ctx)
    {
        if (ctx == current_context.get())
        {
            current_context = nullptr;
        }

        auto iter = std::find_if(begin(all_contexts), end(all_contexts), std::bind(context_equals, ctx, std::placeholders::_1));
        if (iter != end(all_contexts))
        {
            all_contexts.erase(iter);
        }
    }

    std::shared_ptr<context> get_current_context()
    {
        if (!current_context && all_contexts.size() == 0)
        {
            current_context = create_context();
        }

        if (!current_context)
        {
            throw no_context_error();
        }

        return current_context;
    }

    void set_current_context(context* ctx)
    {
        auto iter = std::find_if(begin(all_contexts), end(all_contexts), std::bind(context_equals, ctx, std::placeholders::_1));
        if (iter != end(all_contexts))
        {
            current_context = *iter;
        }
        else
        {
            current_context = nullptr;
        }
    }

    void log_gl_error(const gl_error& error)
    {
        if (current_context && current_context->state().error() == GL_NO_ERROR)
        {
            current_context->state().error() = error.error_code();
        }

        log_message(GL_DEBUG_SOURCE_API_ARB, GL_DEBUG_TYPE_ERROR_ARB, error.error_code(), GL_DEBUG_SEVERITY_HIGH_ARB,
                    format("%s: %s", error.error_code_description().c_str(), error.error_msg().c_str()));
    }

    void log_context_error(const context_error& error)
    {
        log_message(GL_DEBUG_SOURCE_THIRD_PARTY_ARB, GL_DEBUG_TYPE_ERROR_ARB, GL_DEBUG_SEVERITY_HIGH_ARB, 0, error.error_msg());
    }

    void log_message(GLenum source, GLenum type, GLuint id, GLenum severity, const std::string& msg)
    {
        debug_msg_callback msg_callback = nullptr;
        GLvoid* user_param = nullptr;

        if (current_context)
        {
            msg_callback = current_context->log().callback();
            user_param = current_context->log().user_param();
        }
        else
        {
            msg_callback = get_default_debug_msg_callback();
            user_param = nullptr;
        }

        if (msg_callback)
        {
            msg_callback(source, type, id, severity, msg.length(), msg.c_str(), user_param);
        }
    }
}
