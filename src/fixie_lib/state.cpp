#include "fixie_lib/state.hpp"

#include <algorithm>

#include "fixie/fixie_gl_es.h"
#include "fixie_lib/exceptions.hpp"
#include "fixie_lib/debug.hpp"
#include "fixie_lib/util.hpp"

namespace fixie
{
    state::state(const caps& caps, std::unique_ptr<fixie::framebuffer> default_fbo, std::unique_ptr<fixie::vertex_array> default_vao)
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
        , _next_texture_id(1)
        , _bound_textures(caps.max_texture_units())
        , _texture_environments(caps.max_texture_units())
        , _next_framebuffer_id(1)
        , _bound_framebuffer()
        , _next_buffer_id(1)
        , _bound_array_buffer()
        , _bound_element_array_buffer()
        , _next_vertex_array_id(1)
        , _bound_vertex_array()
        , _active_client_texture(0)
        , _shade_model(GL_SMOOTH)
        , _error(GL_NO_ERROR)
    {
        _framebuffers.insert(std::make_pair(0, std::move(default_fbo)));
        bind_framebuffer(default_framebuffer());

        _vertex_arrays.insert(std::make_pair(0, std::move(default_vao)));
        bind_vertex_array(default_vertex_array());

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

    GLuint state::insert_texture(std::unique_ptr<fixie::texture> texture)
    {
        GLuint id = _next_texture_id++;
        _textures[id] = std::move(texture);
        return id;
    }

    void state::delete_texture(GLuint id)
    {
        auto iter = _textures.find(id);
        if (iter != end(_textures))
        {
            _textures.erase(iter);
        }
    }

    std::weak_ptr<fixie::texture> state::texture(GLuint id)
    {
        auto iter = _textures.find(id);
        return (iter != end(_textures)) ? iter->second : std::weak_ptr<fixie::texture>();
    }

    std::weak_ptr<const fixie::texture> state::texture(GLuint id) const
    {
        auto iter = _textures.find(id);
        return (iter != end(_textures)) ? iter->second : std::weak_ptr<fixie::texture>();
    }

    GLuint state::texture_id(std::weak_ptr<const fixie::texture> texture) const
    {
        auto iter = reverse_find(begin(_textures), end(_textures), texture.lock());
        return (iter != end(_textures)) ? iter->first : 0;
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

    GLuint state::insert_renderbuffer(std::unique_ptr<fixie::renderbuffer> renderbuffer)
    {
        GLuint id = _next_renderbuffer_id++;
        _renderbuffers[id] = std::move(renderbuffer);
        return id;
    }

    void state::delete_renderbuffer(GLuint id)
    {
        auto iter = _renderbuffers.find(id);
        if (iter != end(_renderbuffers))
        {
            _renderbuffers.erase(iter);
        }
    }

    std::weak_ptr<fixie::renderbuffer> state::renderbuffer(GLuint id)
    {
        auto iter = _renderbuffers.find(id);
        return (iter != end(_renderbuffers)) ? iter->second : std::weak_ptr<fixie::renderbuffer>();
    }

    std::weak_ptr<const fixie::renderbuffer> state::renderbuffer(GLuint id) const
    {
        auto iter = _renderbuffers.find(id);
        return (iter != end(_renderbuffers)) ? iter->second : std::weak_ptr<fixie::renderbuffer>();
    }

    GLuint state::renderbuffer_id(std::weak_ptr<const fixie::renderbuffer> renderbuffer) const
    {
        auto iter = reverse_find(begin(_renderbuffers), end(_renderbuffers), renderbuffer.lock());
        return (iter != end(_renderbuffers)) ? iter->first : 0;
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

    GLuint state::insert_framebuffer(std::unique_ptr<fixie::framebuffer> framebuffer)
    {
        GLuint id = _next_framebuffer_id++;
        _framebuffers[id] = std::move(framebuffer);
        return id;
    }

    void state::delete_framebuffer(GLuint id)
    {
        auto iter = _framebuffers.find(id);
        if (iter != end(_framebuffers) && id != 0)
        {
            _framebuffers.erase(iter);
        }
    }

    std::weak_ptr<fixie::framebuffer> state::framebuffer(GLuint id)
    {
        auto iter = _framebuffers.find(id);
        return (iter != end(_framebuffers)) ? iter->second : std::weak_ptr<fixie::framebuffer>();
    }

    std::weak_ptr<const fixie::framebuffer> state::framebuffer(GLuint id) const
    {
        auto iter = _framebuffers.find(id);
        return (iter != end(_framebuffers)) ? iter->second : std::weak_ptr<fixie::framebuffer>();
    }

    GLuint state::framebuffer_id(std::weak_ptr<const fixie::framebuffer> framebuffer) const
    {
        auto iter = reverse_find(begin(_framebuffers), end(_framebuffers), framebuffer.lock());
        return (iter != end(_framebuffers)) ? iter->first : 0;
    }

    std::weak_ptr<fixie::framebuffer> state::default_framebuffer()
    {
        return framebuffer(0);
    }

    std::weak_ptr<const fixie::framebuffer> state::default_framebuffer() const
    {
        return framebuffer(0);
    }

    void state::bind_framebuffer(std::weak_ptr<fixie::framebuffer> framebuffer)
    {
        _bound_framebuffer = framebuffer;
    }

    std::weak_ptr<const fixie::framebuffer> state::bound_framebuffer() const
    {
        return _bound_framebuffer.expired() ? default_framebuffer() : _bound_framebuffer;
    }

    std::weak_ptr<fixie::framebuffer> state::bound_framebuffer()
    {
        return _bound_framebuffer.expired() ? default_framebuffer() : _bound_framebuffer;
    }

    GLuint state::insert_buffer(std::unique_ptr<fixie::buffer> buffer)
    {
        GLuint id = _next_buffer_id++;
        _buffers[id] = std::move(buffer);
        return id;
    }

    void state::delete_buffer(GLuint id)
    {
        auto iter = _buffers.find(id);
        if (iter != end(_buffers))
        {
            _buffers.erase(iter);
        }
    }

    std::weak_ptr<fixie::buffer> state::buffer(GLuint id)
    {
        auto iter = _buffers.find(id);
        return (iter != end(_buffers)) ? iter->second : nullptr;
    }

    std::weak_ptr<const fixie::buffer> state::buffer(GLuint id) const
    {
        auto iter = _buffers.find(id);
        return (iter != end(_buffers)) ? iter->second : nullptr;
    }

    GLuint state::buffer_id(std::weak_ptr<const fixie::buffer> buffer) const
    {
        auto iter = reverse_find(begin(_buffers), end(_buffers), buffer.lock());
        return (iter != end(_buffers)) ? iter->first : 0;
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

    GLuint state::insert_vertex_array(std::unique_ptr<fixie::vertex_array> vao)
    {
        GLuint id = _next_vertex_array_id++;
        _vertex_arrays[id] = std::move(vao);
        return id;
    }

    void state::delete_vertex_array(GLuint id)
    {
        auto iter = _vertex_arrays.find(id);
        if (iter != end(_vertex_arrays) && id != 0)
        {
            _vertex_arrays.erase(iter);
        }
    }

    std::weak_ptr<fixie::vertex_array> state::vertex_array(GLuint id)
    {
        auto iter = _vertex_arrays.find(id);
        return (iter != end(_vertex_arrays)) ? iter->second : nullptr;
    }

    std::weak_ptr<const fixie::vertex_array> state::vertex_array(GLuint id) const
    {
        auto iter = _vertex_arrays.find(id);
        return (iter != end(_vertex_arrays)) ? iter->second : nullptr;
    }

    GLuint state::vertex_array_id(std::weak_ptr<const fixie::vertex_array> vertex_array) const
    {
        auto iter = reverse_find(begin(_vertex_arrays), end(_vertex_arrays), vertex_array.lock());
        return (iter != end(_vertex_arrays)) ? iter->first : 0;
    }

    std::weak_ptr<fixie::vertex_array> state::default_vertex_array()
    {
        return vertex_array(0);
    }

    std::weak_ptr<const fixie::vertex_array> state::default_vertex_array() const
    {
        return vertex_array(0);
    }

    void state::bind_vertex_array(std::weak_ptr<fixie::vertex_array> vao)
    {
        _bound_vertex_array = vao;
    }

    std::weak_ptr<const fixie::vertex_array> state::bound_vertex_array() const
    {
        return _bound_vertex_array.expired() ? default_vertex_array() : _bound_vertex_array;
    }

    std::weak_ptr<fixie::vertex_array> state::bound_vertex_array()
    {
        return _bound_vertex_array.expired() ? default_vertex_array() : _bound_vertex_array;
    }

    size_t& state::active_client_texture()
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
