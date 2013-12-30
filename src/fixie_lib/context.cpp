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
    context::context(std::shared_ptr<context_impl> impl, std::shared_ptr<context> share_context)
        : _impl(impl)
        , _state(impl->caps())
        , _resource_manager((share_context != nullptr) ? share_context->_resource_manager : std::make_shared<resource_manager>())
        , _renderbuffers(1)
        , _framebuffers(1)
        , _vertex_arrays(1)
        , _version_string(format("OpenGL ES-%s %u.%u", "CM", 1, 1))
        , _renderer_string(format("fixie (%s)", _impl->renderer_desc().c_str()))
        , _vendor_string("vonture")
        , _extensions(initialize_extensions(impl->caps()))
        , _extension_string(build_extension_string(_extensions))
    {
        _framebuffers.insert_object(0, std::unique_ptr<fixie::framebuffer>(new fixie::framebuffer(std::move(impl->create_default_framebuffer()))), true);
        _state.bind_framebuffer(_framebuffers.get_object(0));

        _vertex_arrays.insert_object(0, std::unique_ptr<fixie::vertex_array>(new fixie::vertex_array(get_default_vertex_array(impl->caps()))), true);
        _state.bind_vertex_array(_vertex_arrays.get_object(0));

        _impl->initialize_state(_state);
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

    GLuint context::create_texture()
    {
        std::unique_ptr<texture_impl> impl = _impl->create_texture();
        std::unique_ptr<fixie::texture> texture = std::unique_ptr<fixie::texture>(new fixie::texture(std::move(impl)));
        return _resource_manager->textures().allocate_object(std::move(texture));
    }

    const handle_manager<GLuint, texture>& context::textures() const
    {
        return _resource_manager->textures();
    }

    handle_manager<GLuint, texture>& context::textures()
    {
        return _resource_manager->textures();
    }

    GLuint context::create_buffer()
    {
        std::unique_ptr<buffer_impl> impl = _impl->create_buffer();
        std::unique_ptr<fixie::buffer> buffer = std::unique_ptr<fixie::buffer>(new fixie::buffer(std::move(impl)));
        return _resource_manager->buffers().allocate_object(std::move(buffer));
    }

    const handle_manager<GLuint, buffer>& context::buffers() const
    {
        return _resource_manager->buffers();
    }

    handle_manager<GLuint, buffer>& context::buffers()
    {
        return _resource_manager->buffers();
    }

    GLuint context::create_renderbuffer()
    {
        std::unique_ptr<renderbuffer_impl> impl = _impl->create_renderbuffer();
        std::unique_ptr<fixie::renderbuffer> renderbuffer = std::unique_ptr<fixie::renderbuffer>(new fixie::renderbuffer(std::move(impl)));
        return _renderbuffers.allocate_object(std::move(renderbuffer));
    }

    const handle_manager<GLuint, renderbuffer>& context::renderbuffers() const
    {
        return _renderbuffers;
    }

    handle_manager<GLuint, renderbuffer>& context::renderbuffers()
    {
        return _renderbuffers;
    }

    GLuint context::create_framebuffer()
    {
        std::unique_ptr<framebuffer_impl> impl = _impl->create_framebuffer();
        std::unique_ptr<fixie::framebuffer> framebuffer = std::unique_ptr<fixie::framebuffer>(new fixie::framebuffer(std::move(impl)));
        return _framebuffers.allocate_object(std::move(framebuffer));
    }

    const handle_manager<GLuint, framebuffer>& context::framebuffers() const
    {
        return _framebuffers;
    }

    handle_manager<GLuint, framebuffer>& context::framebuffers()
    {
        return _framebuffers;
    }

    GLuint context::create_vertex_array()
    {
        std::unique_ptr<fixie::vertex_array> vao = std::unique_ptr<fixie::vertex_array>(new fixie::vertex_array(get_default_vertex_array(_impl->caps())));
        return _vertex_arrays.allocate_object(std::move(vao));
    }

    const handle_manager<GLuint, vertex_array>& context::vertex_arrays() const
    {
        return _vertex_arrays;
    }

    handle_manager<GLuint, vertex_array>& context::vertex_arrays()
    {
        return _vertex_arrays;
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

    fixie::log& context::log()
    {
        return _log;
    }

    const fixie::log& context::log() const
    {
        return _log;
    }

    std::unordered_set<std::string> context::initialize_extensions(const fixie::caps& caps)
    {
        std::unordered_set<std::string> extension_set;
        auto insert_if = [&](GLboolean cond, const std::string& extension){ extension_set.insert(std::move(extension)); };

        insert_if(GL_TRUE, "GL_OES_matrix_get");
        insert_if(caps.supports_framebuffer_objects(), "GL_OES_framebuffer_object");
        insert_if(caps.supports_rgb8_rgba8(), "GL_OES_rgb8_rgba8");
        insert_if(caps.supports_depth24(), "GL_OES_depth24");
        insert_if(caps.supports_depth32(), "GL_OES_depth32");
        insert_if(caps.supports_stencil1(), "GL_OES_stencil1");
        insert_if(caps.supports_stencil4(), "GL_OES_stencil4");
        insert_if(caps.supports_stencil8(), "GL_OES_stencil8");
        insert_if(caps.supports_vertex_array_objects(), "GL_OES_vertex_array_object");

        return extension_set;
    }

    std::string context::build_extension_string(const std::unordered_set<std::string>& extensions)
    {
        std::ostringstream stream;
        std::for_each(begin(extensions), end(extensions), [&](const std::string& extension){ stream << extension << " "; });
        return stream.str();
    }

    const std::shared_ptr<const context_impl> context::impl() const
    {
        return _impl;
    }

    std::shared_ptr<context_impl> context::impl()
    {
        return _impl;
    }
}

#include "null_impl/context.hpp"
#include "desktop_gl_impl/context.hpp"

namespace fixie
{
    std::shared_ptr<context_impl> current_context_impl;
    std::weak_ptr<context> current_context;
    std::set< std::shared_ptr<context> > all_contexts;

    std::shared_ptr<context> create_context(std::shared_ptr<context> share_context)
    {
        if (!current_context_impl)
        {
            current_context_impl = std::make_shared<desktop_gl_impl::context>();
        }

        if (share_context != nullptr && share_context->impl() != current_context_impl)
        {
            log_context_error(context_error("cannot share between contexts with different implementations."));
            return nullptr;
        }

        std::shared_ptr<context> ctx = std::make_shared<context>(current_context_impl, share_context);
        all_contexts.insert(ctx);
        return ctx;
    }

    void destroy_context(std::shared_ptr<context> ctx)
    {
        auto iter = all_contexts.find(ctx);
        if (iter != end(all_contexts))
        {
            all_contexts.erase(iter);
        }

        if (all_contexts.size() == 0)
        {
            current_context_impl = nullptr;
        }
    }

    std::shared_ptr<context> get_context(context* ctx)
    {
        auto iter = std::find_if(begin(all_contexts), end(all_contexts), [&](std::shared_ptr<context> item){ return ctx == item.get(); });
        return iter != end(all_contexts) ? *iter : nullptr;
    }

    std::shared_ptr<context> get_current_context()
    {
        if (all_contexts.size() == 0)
        {
            current_context = create_context(nullptr);
        }

        std::shared_ptr<context> current_locked_context = current_context.lock();

        if (!current_locked_context)
        {
            throw no_context_error();
        }

        return current_locked_context;
    }

    void set_current_context(std::shared_ptr<context> ctx)
    {
        auto iter = all_contexts.find(ctx);
        if (iter != end(all_contexts))
        {
            current_context = *iter;
        }
        else
        {
            current_context = std::weak_ptr<context>();
        }
    }

    void terminate()
    {
        current_context_impl = nullptr;
        current_context = std::weak_ptr<context>();
        all_contexts.clear();
    }

    void log_gl_error(const gl_error& error)
    {
        std::shared_ptr<context> current_locked_context = current_context.lock();
        if (current_locked_context && current_locked_context->state().error() == GL_NO_ERROR)
        {
            current_locked_context->state().error() = error.error_code();
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

        std::shared_ptr<context> current_locked_context = current_context.lock();
        if (current_locked_context)
        {
            msg_callback = current_locked_context->log().callback();
            user_param = current_locked_context->log().user_param();
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
