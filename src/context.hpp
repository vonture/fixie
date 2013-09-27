#ifndef _FIXIE_CONTEXT_HPP_
#define _FIXIE_CONTEXT_HPP_

#include <memory>
#include <vector>

#include "exceptions.hpp"
#include "material.hpp"
#include "light.hpp"

namespace fixie
{
    class context
    {
    public:
        context();

        material& front_material();
        const material& front_material() const;

        material& back_material();
        const material& back_material() const;

        light& lights(size_t idx);
        const light& lights(size_t idx) const;
        size_t light_count() const;

        void push_error(GLenum error);
        GLenum pop_error();
        void clear_errors();

    private:
        material _front_material;
        material _back_material;

        static const size_t _light_count = 8;
        light _lights[_light_count];

        std::vector<GLenum> _errors;
    };

    std::shared_ptr<context> create_context();
    void destroy_context(context* ctx);

    std::shared_ptr<context> get_current_context();
    void set_current_context(context* ctx);

    void log_gl_error(const gl_error& error);
    void log_context_erorr(const context_error& error);
}

#endif //_FIXIE_CONTEXT_HPP_
