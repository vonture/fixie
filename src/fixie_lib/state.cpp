#include "fixie_lib/state.hpp"

#include <algorithm>

#include "fixie/fixie_gl_es.h"
#include "fixie_lib/exceptions.hpp"
#include "fixie_lib/debug.hpp"
#include "fixie_lib/util.hpp"

namespace fixie
{
    state::state(const caps& caps)
        : _viewport_state(default_viewport_state())
        , _scissor_state(default_scissor_state())
        , _color_buffer_state(default_color_buffer_state())
        , _depth_buffer_state(default_depth_buffer_state())
        , _stencil_buffer_state(default_stencil_buffer_state())
        , _point_state(default_point_state())
        , _line_state(default_line_state())
        , _polygon_state(default_polygon_state())
        , _multisample_state(default_multisample_state())
        , _fog_state(default_fog_state())
        , _lighting_state(default_lighting_state(caps))
        , _hint_state(default_hint_state())
        , _pixel_store_state(default_pixel_store_state())
        , _clip_planes(caps.max_clip_planes())
        , _active_texture_unit(0)
        , _matrix_mode(GL_MODELVIEW)
        , _texture_matrix_stacks(caps.max_texture_units())
        , _bound_textures(caps.max_texture_units())
        , _texture_environments(caps.max_texture_units())
        , _bound_framebuffer()
        , _bound_array_buffer()
        , _bound_element_array_buffer()
        , _bound_vertex_array()
        , _active_client_texture(0)
        , _shade_model(GL_SMOOTH)
        , _error(GL_NO_ERROR)
    {
        std::generate(begin(_clip_planes), end(_clip_planes), default_clip_plane);
        std::generate(begin(_texture_environments), end(_texture_environments), default_texture_environment);
    }

    const fixie::viewport_state& state::viewport_state() const
    {
        return _viewport_state;
    }

    fixie::viewport_state& state::viewport_state()
    {
        return _viewport_state;
    }

    const fixie::scissor_state& state::scissor_state() const
    {
        return _scissor_state;
    }

    fixie::scissor_state& state::scissor_state()
    {
        return _scissor_state;
    }

    const fixie::color_buffer_state& state::color_buffer_state() const
    {
        return _color_buffer_state;
    }

    fixie::color_buffer_state& state::color_buffer_state()
    {
        return _color_buffer_state;
    }

    const fixie::depth_buffer_state& state::depth_buffer_state() const
    {
        return _depth_buffer_state;
    }

    fixie::depth_buffer_state& state::depth_buffer_state()
    {
        return _depth_buffer_state;
    }

    const fixie::stencil_buffer_state& state::stencil_buffer_state() const
    {
        return _stencil_buffer_state;
    }

    fixie::stencil_buffer_state& state::stencil_buffer_state()
    {
        return _stencil_buffer_state;
    }

    const fixie::point_state& state::point_state() const
    {
        return _point_state;
    }

    fixie::point_state& state::point_state()
    {
        return _point_state;
    }

    const fixie::line_state& state::line_state() const
    {
        return _line_state;
    }

    fixie::line_state& state::line_state()
    {
        return _line_state;
    }

    const fixie::polygon_state& state::polygon_state() const
    {
        return _polygon_state;
    }

    fixie::polygon_state& state::polygon_state()
    {
        return _polygon_state;
    }

    const fixie::multisample_state& state::multisample_state() const
    {
        return _multisample_state;
    }

    fixie::multisample_state& state::multisample_state()
    {
        return _multisample_state;
    }

    const fixie::fog_state& state::fog_state() const
    {
        return _fog_state;
    }

    fixie::fog_state& state::fog_state()
    {
        return _fog_state;
    }

    const fixie::lighting_state& state::lighting_state() const
    {
        return _lighting_state;
    }

    fixie::lighting_state& state::lighting_state()
    {
        return _lighting_state;
    }

    const fixie::hint_state& state::hint_state() const
    {
        return _hint_state;
    }

    fixie::hint_state& state::hint_state()
    {
        return _hint_state;
    }

    const fixie::pixel_store_state& state::pixel_store_state() const
    {
        return _pixel_store_state;
    }

    fixie::pixel_store_state& state::pixel_store_state()
    {
        return _pixel_store_state;
    }

    fixie::clip_plane& state::clip_plane(size_t idx)
    {
        return _clip_planes[idx];
    }

    const fixie::clip_plane& state::clip_plane(size_t idx) const
    {
        return _clip_planes[idx];
    }

    GLenum& state::matrix_mode()
    {
        return _matrix_mode;
    }

    const GLenum& state::matrix_mode() const
    {
        return _matrix_mode;
    }

    matrix_stack& state::texture_matrix_stack(size_t idx)
    {
        return _texture_matrix_stacks[idx];
    }

    const matrix_stack& state::texture_matrix_stack(size_t idx) const
    {
        return _texture_matrix_stacks[idx];
    }

    matrix_stack& state::model_view_matrix_stack()
    {
        return _model_view_matrix_stack;
    }

    const matrix_stack& state::model_view_matrix_stack() const
    {
        return _model_view_matrix_stack;
    }

    matrix_stack& state::projection_matrix_stack()
    {
        return _projection_matrix_stack;
    }

    const matrix_stack& state::projection_matrix_stack() const
    {
        return _projection_matrix_stack;
    }

    size_t& state::active_texture_unit()
    {
        return _active_texture_unit;
    }

    const size_t& state::active_texture_unit() const
    {
        return _active_texture_unit;
    }

    void state::bind_texture(std::weak_ptr<fixie::texture> texture, size_t unit)
    {
        _bound_textures[unit] = texture;
    }

    std::weak_ptr<const fixie::texture> state::bound_texture(size_t unit) const
    {
        return _bound_textures[unit];
    }

    std::weak_ptr<fixie::texture> state::bound_texture(size_t unit)
    {
        return _bound_textures[unit];
    }

    fixie::texture_environment& state::texture_environment(size_t unit)
    {
        return _texture_environments[unit];
    }

    const fixie::texture_environment& state::texture_environment(size_t unit) const
    {
        return _texture_environments[unit];
    }

    void state::bind_renderbuffer(std::weak_ptr<fixie::renderbuffer> renderbuffer)
    {
        _bound_renderbuffer = renderbuffer;
    }

    std::weak_ptr<const fixie::renderbuffer> state::bound_renderbuffer() const
    {
        return _bound_renderbuffer;
    }

    std::weak_ptr<fixie::renderbuffer> state::bound_renderbuffer()
    {
        return _bound_renderbuffer;
    }

    void state::bind_framebuffer(std::weak_ptr<fixie::framebuffer> framebuffer)
    {
        _bound_framebuffer = framebuffer;
    }

    std::weak_ptr<const fixie::framebuffer> state::bound_framebuffer() const
    {
        return _bound_framebuffer;
    }

    std::weak_ptr<fixie::framebuffer> state::bound_framebuffer()
    {
        return _bound_framebuffer;
    }

    void state::bind_array_buffer(std::weak_ptr<fixie::buffer> buf)
    {
        _bound_array_buffer = buf;
        std::shared_ptr<fixie::buffer> locked_array_buffer = _bound_array_buffer.lock();
        if (locked_array_buffer)
        {
            locked_array_buffer->bind(GL_ARRAY_BUFFER);
            std::shared_ptr<fixie::buffer> locked_element_array_buffer = _bound_element_array_buffer.lock();
            if (locked_element_array_buffer == locked_array_buffer)
            {
                _bound_element_array_buffer.reset();
            }
        }
    }

    std::weak_ptr<const fixie::buffer> state::bound_array_buffer() const
    {
        return _bound_array_buffer;
    }

    std::weak_ptr<fixie::buffer> state::bound_array_buffer()
    {
        return _bound_array_buffer;
    }

    void state::bind_element_array_buffer(std::weak_ptr<fixie::buffer> buf)
    {
        _bound_element_array_buffer = buf.lock();
        std::shared_ptr<fixie::buffer> locked_element_array_buffer = _bound_element_array_buffer.lock();
        if (locked_element_array_buffer)
        {
            locked_element_array_buffer->bind(GL_ELEMENT_ARRAY_BUFFER);
            std::shared_ptr<fixie::buffer> locked_array_buffer = _bound_array_buffer.lock();
            if (locked_array_buffer == locked_element_array_buffer)
            {
                _bound_array_buffer.reset();
            }
        }
    }

    std::weak_ptr<const fixie::buffer> state::bound_element_array_buffer() const
    {
        return _bound_element_array_buffer;
    }

    std::weak_ptr<fixie::buffer> state::bound_element_array_buffer()
    {
        return _bound_element_array_buffer;
    }

    void state::bind_vertex_array(std::weak_ptr<fixie::vertex_array> vao)
    {
        _bound_vertex_array = vao;
    }

    std::weak_ptr<const fixie::vertex_array> state::bound_vertex_array() const
    {
        return _bound_vertex_array;
    }

    std::weak_ptr<fixie::vertex_array> state::bound_vertex_array()
    {
        return _bound_vertex_array;
    }

    size_t& state::active_client_texture()
    {
        return _active_client_texture;
    }

    const size_t& state::active_client_texture() const
    {
        return _active_client_texture;
    }

    GLenum& state::shade_model()
    {
        return _shade_model;
    }

    const GLenum& state::shade_model() const
    {
        return _shade_model;
    }

    GLenum& state::error()
    {
        return _error;
    }

    const GLenum& state::error() const
    {
        return _error;
    }
}
