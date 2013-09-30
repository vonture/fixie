#ifndef _FIXIE_CONTEXT_HPP_
#define _FIXIE_CONTEXT_HPP_

#include <memory>

#include "exceptions.hpp"
#include "material.hpp"
#include "light.hpp"
#include "light_model.hpp"
#include "vector.hpp"
#include "matrix.hpp"
#include "matrix_stack.hpp"

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

        light_model& light_model_properties();
        const light_model& light_model_properties() const;

        vector4& clip_plane(size_t idx);
        const vector4& clip_plane(size_t idx) const;
        size_t clip_plane_count() const;

        size_t& active_texture_unit();
        const size_t& active_texture_unit() const;

        GLenum& matrix_mode();
        const GLenum& matrix_mode() const;

        matrix_stack& texture_matrix_stack(size_t idx);
        const matrix_stack& texture_matrix_stack(size_t idx) const;

        matrix_stack& model_view_matrix_stack();
        const matrix_stack& model_view_matrix_stack() const;

        matrix_stack& projection_matrix_stack();
        const matrix_stack& projection_matrix_stack() const;

        matrix_stack& active_matrix_stack();
        const matrix_stack& active_matrix_stack() const;

        GLenum& error();
        const GLenum& error() const;

    private:
        material _front_material;
        material _back_material;

        static const size_t _light_count = 8;
        light _lights[_light_count];

        light_model _light_model;

        static const size_t _clip_plane_count = 6;
        vector4 _clip_planes[_clip_plane_count];

        static const size_t _texture_unit_count = 32;
        size_t _active_texture_unit;

        GLenum _matrix_mode;

        matrix_stack _texture_matrix_stacks[_texture_unit_count];
        matrix_stack _model_view_matrix_stack;
        matrix_stack _projection_matrix_stack;

        GLenum _error;
    };

    std::shared_ptr<context> create_context();
    void destroy_context(context* ctx);

    std::shared_ptr<context> get_current_context();
    void set_current_context(context* ctx);

    void log_gl_error(const gl_error& error);
    void log_context_error(const context_error& error);
}

#endif //_FIXIE_CONTEXT_HPP_
