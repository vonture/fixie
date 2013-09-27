#include "context.hpp"
#include "exceptions.hpp"

#include <set>
#include <algorithm>
#include <functional>

namespace fixie
{
    context::context()
        : _front_material(get_default_material())
        , _back_material(get_default_material())
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

    void context::push_error(GLenum error)
    {
        _errors.push_back(error);
    }

    GLenum context::pop_error()
    {
        GLenum error = 0;
        if (_errors.size() > 0)
        {
            error = _errors.back();
            _errors.pop_back();
        }
        return error;
    }

    void context::clear_errors()
    {
        _errors.clear();
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
        if (current_context)
        {
            current_context->push_error(error.error_code());
        }

        // TODO: log error message
    }

    void log_context_erorr(const context_error& error)
    {
        // TODO: log error message
    }
}
