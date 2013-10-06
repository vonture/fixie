#ifndef _STATE_HPP_
#define _STATE_HPP_

#include <memory>
#include <unordered_map>
#include <vector>

#include "caps.hpp"
#include "rectangle.hpp"
#include "range.hpp"
#include "material.hpp"
#include "light.hpp"
#include "light_model.hpp"
#include "vector.hpp"
#include "matrix.hpp"
#include "matrix_stack.hpp"
#include "texture.hpp"
#include "buffer.hpp"
#include "vertex_attribute.hpp"

namespace fixie
{
    class state
    {
    public:
        state(const caps& caps);

        color& clear_color();
        const color& clear_color() const;

        GLclampf& clear_depth();
        const GLclampf& clear_depth() const;

        GLint& clear_stencil();
        const GLint& clear_stencil() const;

        GLboolean& depth_test();
        const GLboolean& depth_test() const;

        range& depth_range();
        const range& depth_range() const;

        GLenum& depth_func();
        const GLenum& depth_func() const;

        rectangle& viewport();
        const rectangle& viewport() const;

        GLboolean& scissor_test();
        const GLboolean& scissor_test() const;

        rectangle& scissor();
        const rectangle& scissor() const;

        material& front_material();
        const material& front_material() const;

        material& back_material();
        const material& back_material() const;

        light& lights(size_t idx);
        const light& lights(size_t idx) const;

        fixie::light_model& light_model();
        const fixie::light_model& light_model() const;

        vector4& clip_plane(size_t idx);
        const vector4& clip_plane(size_t idx) const;

        GLenum& matrix_mode();
        const GLenum& matrix_mode() const;

        matrix_stack& texture_matrix_stack(size_t idx);
        const matrix_stack& texture_matrix_stack(size_t idx) const;

        matrix_stack& model_view_matrix_stack();
        const matrix_stack& model_view_matrix_stack() const;

        matrix_stack& projection_matrix_stack();
        const matrix_stack& projection_matrix_stack() const;

        GLuint insert_texture(std::shared_ptr<fixie::texture> texture);
        void delete_texture(GLuint id);
        std::shared_ptr<fixie::texture> texture(GLuint id);
        std::shared_ptr<const fixie::texture> texture(GLuint id) const;

        size_t& active_texture_unit();
        const size_t& active_texture_unit() const;

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

        fixie::vertex_attribute& vertex_attribute();
        const fixie::vertex_attribute& vertex_attribute() const;

        fixie::vertex_attribute& normal_attribute();
        const fixie::vertex_attribute& normal_attribute() const;

        fixie::vertex_attribute& color_attribute();
        const fixie::vertex_attribute& color_attribute() const;

        size_t& active_client_texture();
        const size_t& active_client_texture() const;

        fixie::vertex_attribute& texcoord_attribute(size_t unit);
        const fixie::vertex_attribute& texcoord_attribute(size_t unit) const;

        GLenum& error();
        const GLenum& error() const;

    private:
        color _clear_color;
        GLclampf _clear_depth;
        GLint _clear_stencil;

        GLboolean _depth_test;
        range _depth_range;
        GLenum _depth_func;

        rectangle _viewport;

        GLboolean _scissor_test;
        rectangle _scissor;

        material _front_material;
        material _back_material;

        std::vector<light> _lights;

        fixie::light_model _light_model;

        std::vector<vector4> _clip_planes;

        size_t _active_texture_unit;

        GLenum _matrix_mode;

        std::vector<matrix_stack> _texture_matrix_stacks;
        matrix_stack _model_view_matrix_stack;
        matrix_stack _projection_matrix_stack;

        GLuint _next_texture_id;
        std::unordered_map< GLuint, std::shared_ptr<fixie::texture> > _textures;
        std::vector< std::shared_ptr<fixie::texture> > _bound_textures;

        GLuint _next_buffer_id;
        std::unordered_map< GLuint, std::shared_ptr<fixie::buffer> > _buffers;
        std::shared_ptr<fixie::buffer> _bound_array_buffer;
        std::shared_ptr<fixie::buffer> _bound_element_array_buffer;

        fixie::vertex_attribute _vertex_attribute;
        fixie::vertex_attribute _normal_attribute;
        fixie::vertex_attribute _color_attribute;
        size_t _active_client_texture;
        std::vector<fixie::vertex_attribute> _texcoord_attributes;

        GLenum _error;
    };
}

#endif // STATE_HPP_
