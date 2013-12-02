#ifndef _STATE_HPP_
#define _STATE_HPP_

#include <memory>
#include <unordered_map>
#include <vector>

#include "fixie_lib/caps.hpp"
#include "fixie_lib/depth_stencil_state.hpp"
#include "fixie_lib/clear_state.hpp"
#include "fixie_lib/rasterizer_state.hpp"
#include "fixie_lib/rectangle.hpp"
#include "fixie_lib/range.hpp"
#include "fixie_lib/lighting_state.hpp"
#include "fixie_lib/color.hpp"
#include "fixie_lib/clip_plane.hpp"
#include "fixie_lib/vector.hpp"
#include "fixie_lib/matrix.hpp"
#include "fixie_lib/matrix_stack.hpp"
#include "fixie_lib/texture.hpp"
#include "fixie_lib/renderbuffer.hpp"
#include "fixie_lib/buffer.hpp"
#include "fixie_lib/framebuffer.hpp"
#include "fixie_lib/vertex_array.hpp"
#include "fixie_lib/texture_environment.hpp"

namespace fixie
{
    class state
    {
    public:
        state(const caps& caps, std::unique_ptr<fixie::framebuffer> default_fbo, std::unique_ptr<fixie::vertex_array> default_vao);

        const fixie::clear_state& clear_state() const;
        fixie::clear_state& clear_state();

        const fixie::depth_stencil_state& depth_stencil_state() const;
        fixie::depth_stencil_state& depth_stencil_state();

        const fixie::rasterizer_state& rasterizer_state() const;
        fixie::rasterizer_state& rasterizer_state();

        const fixie::lighting_state& lighting_state() const;
        fixie::lighting_state& lighting_state();

        fixie::clip_plane& clip_plane(size_t idx);
        const fixie::clip_plane& clip_plane(size_t idx) const;

        GLenum& matrix_mode();
        const GLenum& matrix_mode() const;

        matrix_stack& texture_matrix_stack(size_t idx);
        const matrix_stack& texture_matrix_stack(size_t idx) const;

        matrix_stack& model_view_matrix_stack();
        const matrix_stack& model_view_matrix_stack() const;

        matrix_stack& projection_matrix_stack();
        const matrix_stack& projection_matrix_stack() const;

        GLuint insert_texture(std::unique_ptr<fixie::texture> texture);
        void delete_texture(GLuint id);
        std::weak_ptr<fixie::texture> texture(GLuint id);
        std::weak_ptr<const fixie::texture> texture(GLuint id) const;

        size_t& active_texture_unit();
        const size_t& active_texture_unit() const;

        void bind_texture(std::weak_ptr<fixie::texture> texture, size_t unit);
        std::weak_ptr<const fixie::texture> bound_texture(size_t unit) const;
        std::weak_ptr<fixie::texture> bound_texture(size_t unit);

        fixie::texture_environment& texture_environment(size_t unit);
        const fixie::texture_environment& texture_environment(size_t unit) const;

        GLuint insert_renderbuffer(std::unique_ptr<fixie::renderbuffer> renderbuffer);
        void delete_renderbuffer(GLuint id);
        std::weak_ptr<fixie::renderbuffer> renderbuffer(GLuint id);
        std::weak_ptr<const fixie::renderbuffer> renderbuffer(GLuint id) const;

        void bind_renderbuffer(std::weak_ptr<fixie::renderbuffer> renderbuffer);
        std::weak_ptr<const fixie::renderbuffer> bound_renderbuffer() const;
        std::weak_ptr<fixie::renderbuffer> bound_renderbuffer();

        GLuint insert_framebuffer(std::unique_ptr<fixie::framebuffer> framebuffer);
        void delete_framebuffer(GLuint id);
        std::weak_ptr<fixie::framebuffer> framebuffer(GLuint id);
        std::weak_ptr<const fixie::framebuffer> framebuffer(GLuint id) const;
        std::weak_ptr<fixie::framebuffer> default_framebuffer();
        std::weak_ptr<const fixie::framebuffer> default_framebuffer() const;

        void bind_framebuffer(std::weak_ptr<fixie::framebuffer> framebuffer);
        std::weak_ptr<const fixie::framebuffer> bound_framebuffer() const;
        std::weak_ptr<fixie::framebuffer> bound_framebuffer();

        GLuint insert_buffer(std::unique_ptr<fixie::buffer> buffer);
        void delete_buffer(GLuint id);
        std::weak_ptr<fixie::buffer> buffer(GLuint id);
        std::weak_ptr<const fixie::buffer> buffer(GLuint id) const;

        void bind_array_buffer(std::weak_ptr<fixie::buffer> buf);
        std::weak_ptr<const fixie::buffer> bound_array_buffer() const;
        std::weak_ptr<fixie::buffer> bound_array_buffer();

        void bind_element_array_buffer(std::weak_ptr<fixie::buffer> buf);
        std::weak_ptr<const fixie::buffer> bound_element_array_buffer() const;
        std::weak_ptr<fixie::buffer> bound_element_array_buffer();

        GLuint insert_vertex_array(std::unique_ptr<fixie::vertex_array> vao);
        void delete_vertex_array(GLuint id);
        std::weak_ptr<fixie::vertex_array> vertex_array(GLuint id);
        std::weak_ptr<const fixie::vertex_array> vertex_array(GLuint id) const;
        std::weak_ptr<fixie::vertex_array> default_vertex_array();
        std::weak_ptr<const fixie::vertex_array> default_vertex_array() const;

        void bind_vertex_array(std::weak_ptr<fixie::vertex_array> vao);
        std::weak_ptr<const fixie::vertex_array> bound_vertex_array() const;
        std::weak_ptr<fixie::vertex_array> bound_vertex_array();

        size_t& active_client_texture();
        const size_t& active_client_texture() const;

        GLenum& shade_model();
        const GLenum& shade_model() const;

        GLenum& error();
        const GLenum& error() const;

    private:
        fixie::clear_state _clear_state;
        fixie::depth_stencil_state _depth_stencil_state;
        fixie::rasterizer_state _rasterizer_state;
        fixie::lighting_state _lighting_state;

        std::vector<fixie::clip_plane> _clip_planes;

        size_t _active_texture_unit;

        GLenum _matrix_mode;

        std::vector<matrix_stack> _texture_matrix_stacks;
        matrix_stack _model_view_matrix_stack;
        matrix_stack _projection_matrix_stack;

        GLuint _next_texture_id;
        std::unordered_map< GLuint, std::shared_ptr<fixie::texture> > _textures;
        std::vector< std::weak_ptr<fixie::texture> > _bound_textures;
        std::vector<fixie::texture_environment> _texture_environments;

        GLuint _next_renderbuffer_id;
        std::unordered_map< GLuint, std::shared_ptr<fixie::renderbuffer> > _renderbuffers;
        std::weak_ptr<fixie::renderbuffer> _bound_renderbuffer;

        GLuint _next_framebuffer_id;
        std::unordered_map< GLuint, std::shared_ptr<fixie::framebuffer> > _framebuffers;
        std::weak_ptr<fixie::framebuffer> _bound_framebuffer;

        GLuint _next_buffer_id;
        std::unordered_map< GLuint, std::shared_ptr<fixie::buffer> > _buffers;
        std::weak_ptr<fixie::buffer> _bound_array_buffer;
        std::weak_ptr<fixie::buffer> _bound_element_array_buffer;

        GLuint _next_vertex_array_id;
        std::unordered_map< GLuint, std::shared_ptr<fixie::vertex_array> > _vertex_arrays;
        std::weak_ptr<fixie::vertex_array> _bound_vertex_array;

        size_t _active_client_texture;

        GLenum _shade_model;

        GLenum _error;
    };
}

#endif // STATE_HPP_
