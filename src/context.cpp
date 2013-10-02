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
    context::context()
        : _front_material(get_default_material())
        , _back_material(get_default_material())
        , _active_texture_unit(0)
        , _matrix_mode(GL_MODELVIEW)
        , _error(GL_NO_ERROR)
    {
        for (size_t i = 0; i < _light_count; i++)
        {
            _lights[i] = get_default_light(i);
        }
    }

    material& context::front_material()
    {
        return _front_material;
    }

    const material& context::front_material() const
    {
        return _front_material;
    }

    material& context::back_material()
    {
        return _back_material;
    }

    const material& context::back_material() const
    {
        return _back_material;
    }

    light& context::lights(size_t idx)
    {
        return _lights[idx];
    }

    const light& context::lights(size_t idx) const
    {
        return _lights[idx];
    }

    size_t context::light_count() const
    {
        return _light_count;
    }

    light_model& context::light_model_properties()
    {
        return _light_model;
    }

    const light_model& context::light_model_properties() const
    {
        return _light_model;
    }

    vector4& context::clip_plane(size_t idx)
    {
        return _clip_planes[idx];
    }

    const vector4& context::clip_plane(size_t idx) const
    {
        return _clip_planes[idx];
    }

    size_t context::clip_plane_count() const
    {
        return _clip_plane_count;
    }

    size_t& context::active_texture_unit()
    {
        return _active_texture_unit;
    }

    const size_t& context::active_texture_unit() const
    {
        return _active_texture_unit;
    }

    GLenum& context::matrix_mode()
    {
        return _matrix_mode;
    }

    const GLenum& context::matrix_mode() const
    {
        return _matrix_mode;
    }

    matrix_stack& context::texture_matrix_stack(size_t idx)
    {
        return _texture_matrix_stacks[idx];
    }

    const matrix_stack& context::texture_matrix_stack(size_t idx) const
    {
        return _texture_matrix_stacks[idx];
    }

    matrix_stack& context::model_view_matrix_stack()
    {
        return _model_view_matrix_stack;
    }

    const matrix_stack& context::model_view_matrix_stack() const
    {
        return _model_view_matrix_stack;
    }

    matrix_stack& context::projection_matrix_stack()
    {
        return _projection_matrix_stack;
    }

    const matrix_stack& context::projection_matrix_stack() const
    {
        return _projection_matrix_stack;
    }

    matrix_stack& context::active_matrix_stack()
    {
        switch (_matrix_mode)
        {
        case GL_TEXTURE:
            return _texture_matrix_stacks[_active_texture_unit];

        case GL_MODELVIEW:
            return _model_view_matrix_stack;

        case GL_PROJECTION:
            return _projection_matrix_stack;

        default:
            UNREACHABLE();
            throw context_error("unknown matrix mode.");
        }
    }

    const matrix_stack& context::active_matrix_stack() const
    {
        return const_cast<context*>(this)->active_matrix_stack();
    }

    log& context::logger()
    {
        return _log;
    }

    const log& context::logger() const
    {
        return _log;
    }

    GLenum& context::error()
    {
        return _error;
    }

    const GLenum& context::error() const
    {
        return _error;
    }

    std::shared_ptr<context> current_context;
    std::set< std::shared_ptr<context> > all_contexts;

    std::shared_ptr<context> create_context()
    {
        std::shared_ptr<context> ctx(new context());
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

        auto iter = std::find_if(all_contexts.begin(), all_contexts.end(), std::bind(context_equals, ctx, std::placeholders::_1));
        if (iter != all_contexts.end())
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
        auto iter = std::find_if(all_contexts.begin(), all_contexts.end(), std::bind(context_equals, ctx, std::placeholders::_1));
        if (iter != all_contexts.end())
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
        if (current_context && current_context->error() == GL_NO_ERROR)
        {
            current_context->error() = error.error_code();
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
            msg_callback = current_context->logger().callback();
            user_param = current_context->logger().user_param();
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
