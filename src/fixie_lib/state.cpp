#include "fixie_lib/state.hpp"

#include <algorithm>

#include "fixie/fixie_gl_es.h"
#include "fixie_lib/exceptions.hpp"
#include "fixie_lib/debug.hpp"

namespace fixie
{
    state::state(const caps& caps, std::unique_ptr<fixie::framebuffer> default_fbo, std::unique_ptr<fixie::vertex_array> default_vao)
        : _viewport_state(get_default_viewport_state())
        , _clear_state(get_default_clear_state())
        , _depth_stencil_state(get_default_depth_stencil_state())
        , _rasterizer_state(get_default_rasterizer_state())
        , _lighting_state(get_default_lighting_state(caps))
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

        std::generate(begin(_clip_planes), end(_clip_planes), get_default_clip_plane);
        std::generate(begin(_texture_environments), end(_texture_environments), get_default_texture_environment);
    }

    const fixie::viewport_state& state::viewport_state() const
    {
        return _viewport_state;
    }

    fixie::viewport_state& state::viewport_state()
    {
        return _viewport_state;
    }

    const fixie::clear_state& state::clear_state() const
    {
        return _clear_state;
    }

    fixie::clear_state& state::clear_state()
    {
        return _clear_state;
    }

    const fixie::depth_stencil_state& state::depth_stencil_state() const
    {
        return _depth_stencil_state;
    }

    fixie::depth_stencil_state& state::depth_stencil_state()
    {
        return _depth_stencil_state;
    }

    const fixie::rasterizer_state& state::rasterizer_state() const
    {
        return _rasterizer_state;
    }

    fixie::rasterizer_state& state::rasterizer_state()
    {
        return _rasterizer_state;
    }

    const fixie::lighting_state& state::lighting_state() const
    {
        return _lighting_state;
    }

    fixie::lighting_state& state::lighting_state()
    {
        return _lighting_state;
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
