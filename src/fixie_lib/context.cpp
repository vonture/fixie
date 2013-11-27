#include "fixie_lib/context.hpp"
#include "fixie_lib/exceptions.hpp"
#include "fixie/fixie_gl_es.h"
#include "fixie_lib/debug.hpp"
#include "fixie_lib/util.hpp"

#include <set>
#include <algorithm>
#include <functional>

namespace fixie
{
    context::context(std::shared_ptr<context_impl> impl)
        : _impl(impl)
        , _state(impl->caps(),
                 std::unique_ptr<fixie::framebuffer>(new fixie::framebuffer(std::move(impl->create_default_framebuffer()))),
                 std::unique_ptr<fixie::vertex_array>(new fixie::vertex_array(get_default_vertex_array(impl->caps()))))
        , _version_string(format("OpenGL ES-%s %u.%u", "CM", 1, 1))
        , _renderer_string(format("fixie (%s)", _impl->renderer_desc().c_str()))
        , _vendor_string("vonture")
        , _extensions(initialize_extensions(impl->caps()))
        , _extension_string(build_extension_string(_extensions))
    {
        _impl->initialize_state(_state);
    }

    GLuint context::create_texture()
    {
        std::unique_ptr<texture_impl> impl = _impl->create_texture();
        std::unique_ptr<fixie::texture> texture = std::unique_ptr<fixie::texture>(new fixie::texture(std::move(impl)));
        return _state.insert_texture(std::move(texture));
    }

    GLuint context::create_framebuffer()
    {
        std::unique_ptr<framebuffer_impl> impl = _impl->create_framebuffer();
        std::unique_ptr<fixie::framebuffer> framebuffer = std::unique_ptr<fixie::framebuffer>(new fixie::framebuffer(std::move(impl)));
        return _state.insert_framebuffer(std::move(framebuffer));
    }

    GLuint context::create_buffer()
    {
        std::unique_ptr<buffer_impl> impl = _impl->create_buffer();
        std::unique_ptr<fixie::buffer> buffer = std::unique_ptr<fixie::buffer>(new fixie::buffer(std::move(impl)));
        return _state.insert_buffer(std::move(buffer));
    }

    GLuint context::create_vertex_array()
    {
        std::unique_ptr<fixie::vertex_array> buffer = std::unique_ptr<fixie::vertex_array>(new fixie::vertex_array(get_default_vertex_array(_impl->caps())));
        return _state.insert_vertex_array(std::move(buffer));
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

    void context::flush()
    {
        _impl->flush();
    }

    void context::finish()
    {
        _impl->finish();
    }

    std::unordered_set<std::string> context::initialize_extensions(const fixie::caps& caps)
    {
        std::unordered_set<std::string> extension_set;
        auto insert_if = [&](GLboolean cond, const std::string& extension){ extension_set.insert(std::move(extension)); };

        insert_if(caps.supports_framebuffer_objects(), "GL_OES_framebuffer_object");

        return extension_set;
    }

    std::string context::build_extension_string(std::unordered_set<std::string> extensions)
    {
        std::ostringstream stream;
        std::for_each(begin(extensions), end(extensions), [&](const std::string& extension){ stream << extension << " "; });
        return stream.str();
    }
}

#include "null_impl/context.hpp"
#include "desktop_gl_impl/context.hpp"

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

        if (all_contexts.size() == 0)
        {
            current_context_impl = nullptr;
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

    void terminate()
    {
        current_context_impl = nullptr;
        current_context = nullptr;
        all_contexts.clear();
    }

    void log_gl_error(const gl_error& error)
    {
        if (current_context && current_context->state().error() == GL_NO_ERROR)
        {
            current_context->state().error() = error.error_code();
        }

        log_message(GL_DEBUG_SOURCE_API_KHR, GL_DEBUG_TYPE_ERROR_KHR, error.error_code(), GL_DEBUG_SEVERITY_HIGH_KHR,
                    format("%s: %s", error.error_code_description().c_str(), error.error_msg().c_str()));
    }

    void log_context_error(const context_error& error)
    {
        log_message(GL_DEBUG_SOURCE_THIRD_PARTY_KHR, GL_DEBUG_TYPE_ERROR_KHR, GL_DEBUG_SEVERITY_HIGH_KHR, 0, error.error_msg());
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
            msg_callback(source, type, id, severity, static_cast<GLsizei>(msg.length()), msg.c_str(), user_param);
        }
    }
}
