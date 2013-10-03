#ifndef _FIXIE_CONTEXT_HPP_
#define _FIXIE_CONTEXT_HPP_

#include <memory>
#include <unordered_map>

#include "exceptions.hpp"
#include "material.hpp"
#include "light.hpp"
#include "light_model.hpp"
#include "vector.hpp"
#include "matrix.hpp"
#include "matrix_stack.hpp"
#include "texture.hpp"
#include "buffer.hpp"
#include "log.hpp"

namespace fixie
{
    class context_impl
    {
    public:
        virtual std::shared_ptr<texture_impl> create_texture() = 0;
        virtual std::shared_ptr<buffer_impl> create_buffer() = 0;
    };

    class context
    {
    public:
        context(std::shared_ptr<context_impl> impl);

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

        GLuint create_texture();
        void delete_texture(GLuint id);
        std::shared_ptr<fixie::texture> texture(GLuint id);
        std::shared_ptr<const fixie::texture> texture(GLuint id) const;

        GLuint create_buffer();
        void delete_buffer(GLuint id);
        std::shared_ptr<fixie::buffer> buffer(GLuint id);
        std::shared_ptr<const fixie::buffer> buffer(GLuint id) const;

        log& logger();
        const log& logger() const;

        GLenum& error();
        const GLenum& error() const;

    private:
        std::shared_ptr<context_impl> _impl;

        material _front_material;
        material _back_material;

        static const size_t _light_count = 8;
        light _lights[_light_count];

        fixie::light_model _light_model;

        static const size_t _clip_plane_count = 6;
        vector4 _clip_planes[_clip_plane_count];

        static const size_t _texture_unit_count = 32;
        size_t _active_texture_unit;

        GLenum _matrix_mode;

        matrix_stack _texture_matrix_stacks[_texture_unit_count];
        matrix_stack _model_view_matrix_stack;
        matrix_stack _projection_matrix_stack;

        GLuint _next_texture_id;
        std::unordered_map< GLuint, std::shared_ptr<fixie::texture> > _textures;

        GLuint _next_buffer_id;
        std::unordered_map< GLuint, std::shared_ptr<fixie::buffer> > _buffers;

        log _log;

        GLenum _error;
    };

    std::shared_ptr<context> create_context();
    void destroy_context(context* ctx);

    std::shared_ptr<context> get_current_context();
    void set_current_context(context* ctx);

    void log_gl_error(const gl_error& error);
    void log_context_error(const context_error& error);
    void log_message(GLenum source, GLenum type, GLuint id, GLenum severity, const std::string& msg);
}

#endif //_FIXIE_CONTEXT_HPP_
