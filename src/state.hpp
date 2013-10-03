#ifndef _STATE_HPP_
#define _STATE_HPP_

#include <memory>
#include <unordered_map>
#include <array>

#include "material.hpp"
#include "light.hpp"
#include "light_model.hpp"
#include "vector.hpp"
#include "matrix.hpp"
#include "matrix_stack.hpp"
#include "texture.hpp"
#include "buffer.hpp"

namespace fixie
{
    class state
    {
    public:
        state();

        color& clear_color();
        const color& clear_color() const;

        GLclampf& clear_depth();
        const GLclampf& clear_depth() const;

        GLint& clear_stencil();
        const GLint& clear_stencil() const;

        material& front_material();
        const material& front_material() const;

        material& back_material();
        const material& back_material() const;

        light& lights(size_t idx);
        const light& lights(size_t idx) const;
        size_t light_count() const;

        fixie::light_model& light_model();
        const fixie::light_model& light_model() const;

        vector4& clip_plane(size_t idx);
        const vector4& clip_plane(size_t idx) const;
        size_t clip_plane_count() const;

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

        GLuint insert_texture(std::shared_ptr<fixie::texture> texture);
        void delete_texture(GLuint id);
        std::shared_ptr<fixie::texture> texture(GLuint id);
        std::shared_ptr<const fixie::texture> texture(GLuint id) const;

        size_t& active_texture_unit();
        const size_t& active_texture_unit() const;
        size_t texture_unit_count() const;

        std::shared_ptr<fixie::texture>& bound_texture(size_t unit);
        std::shared_ptr<const fixie::texture> bound_texture(size_t unit) const;

        GLuint insert_buffer(std::shared_ptr<fixie::buffer> buffer);
        void delete_buffer(GLuint id);
        std::shared_ptr<fixie::buffer> buffer(GLuint id);
        std::shared_ptr<const fixie::buffer> buffer(GLuint id) const;

        std::shared_ptr<fixie::buffer>& bound_array_buffer();
        std::shared_ptr<const fixie::buffer> bound_array_buffer() const;

        std::shared_ptr<fixie::buffer>& bound_element_array_buffer();
        std::shared_ptr<const fixie::buffer> bound_element_array_buffer() const;

        GLenum& error();
        const GLenum& error() const;

    private:
        color _clear_color;
        GLclampf _clear_depth;
        GLint _clear_stencil;

        material _front_material;
        material _back_material;

        static const size_t _light_count = 8;
        std::array<light, _light_count> _lights;

        fixie::light_model _light_model;

        static const size_t _clip_plane_count = 6;
        std::array<vector4, _clip_plane_count> _clip_planes;

        static const size_t _texture_unit_count = 32;
        size_t _active_texture_unit;

        GLenum _matrix_mode;

        std::array<matrix_stack, _texture_unit_count> _texture_matrix_stacks;
        matrix_stack _model_view_matrix_stack;
        matrix_stack _projection_matrix_stack;

        GLuint _next_texture_id;
        std::unordered_map< GLuint, std::shared_ptr<fixie::texture> > _textures;
        std::array<std::shared_ptr<fixie::texture>, _texture_unit_count> _bound_textures;

        GLuint _next_buffer_id;
        std::unordered_map< GLuint, std::shared_ptr<fixie::buffer> > _buffers;
        std::shared_ptr<fixie::buffer> _bound_array_buffer;
        std::shared_ptr<fixie::buffer> _bound_element_array_buffer;

        GLenum _error;
    };
}

#endif // STATE_HPP_
