#include "state.hpp"

#include "fixie_gl_es.h"
#include "exceptions.hpp"
#include "debug.hpp"

namespace fixie
{
    state::state()
        : _front_material(get_default_material())
        , _back_material(get_default_material())
        , _active_texture_unit(0)
        , _matrix_mode(GL_MODELVIEW)
        , _next_texture_id(1)
        , _next_buffer_id(1)
        , _error(GL_NO_ERROR)
    {
        for (size_t i = 0; i < _light_count; i++)
        {
            _lights[i] = get_default_light(i);
        }
    }

    color& state::clear_color()
    {
        return _clear_color;
    }

    const color& state::clear_color() const
    {
        return _clear_color;
    }

    GLclampf& state::clear_depth()
    {
        return _clear_depth;
    }

    const GLclampf& state::clear_depth() const
    {
        return _clear_depth;
    }

    GLint& state::clear_stencil()
    {
        return _clear_stencil;
    }

    const GLint& state::clear_stencil() const
    {
        return _clear_stencil;
    }

    material& state::front_material()
    {
        return _front_material;
    }

    const material& state::front_material() const
    {
        return _front_material;
    }

    material& state::back_material()
    {
        return _back_material;
    }

    const material& state::back_material() const
    {
        return _back_material;
    }

    light& state::lights(size_t idx)
    {
        return _lights[idx];
    }

    const light& state::lights(size_t idx) const
    {
        return _lights[idx];
    }

    size_t state::light_count() const
    {
        return _light_count;
    }

    fixie::light_model& state::light_model()
    {
        return _light_model;
    }

    const fixie::light_model& state::light_model() const
    {
        return _light_model;
    }

    vector4& state::clip_plane(size_t idx)
    {
        return _clip_planes[idx];
    }

    const vector4& state::clip_plane(size_t idx) const
    {
        return _clip_planes[idx];
    }

    size_t state::clip_plane_count() const
    {
        return _clip_plane_count;
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

    matrix_stack& state::active_matrix_stack()
    {
        switch (_matrix_mode)
        {
        case GL_TEXTURE:
            return _texture_matrix_stacks[_active_texture_unit];

        case GL_MODELVIEW:
            return _model_view_matrix_stack;

        case GL_PROJECTION:
            return _projection_matrix_stack;

        default:
            UNREACHABLE();
            throw state_error("unknown matrix mode.");
        }
    }

    const matrix_stack& state::active_matrix_stack() const
    {
        return const_cast<state*>(this)->active_matrix_stack();
    }

    GLenum& state::error()
    {
        return _error;
    }

    const GLenum& state::error() const
    {
        return _error;
    }

    GLuint state::insert_texture(std::shared_ptr<fixie::texture> texture)
    {
        GLuint id = _next_texture_id++;
        _textures[id] = texture;
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

    std::shared_ptr<fixie::texture> state::texture(GLuint id)
    {
        auto iter = _textures.find(id);
        return (iter != end(_textures)) ? iter->second : nullptr;
    }

    std::shared_ptr<const fixie::texture> state::texture(GLuint id) const
    {
        auto iter = _textures.find(id);
        return (iter != end(_textures)) ? iter->second : nullptr;
    }

    size_t& state::active_texture_unit()
    {
        return _active_texture_unit;
    }

    const size_t& state::active_texture_unit() const
    {
        return _active_texture_unit;
    }

    size_t state::texture_unit_count() const
    {
        return _texture_unit_count;
    }

    std::shared_ptr<fixie::texture>& state::bound_texture(size_t unit)
    {
        return _bound_textures[unit];
    }

    std::shared_ptr<const fixie::texture> state::bound_texture(size_t unit) const
    {
        return _bound_textures[unit];
    }

    GLuint state::insert_buffer(std::shared_ptr<fixie::buffer> buffer)
    {
        GLuint id = _next_buffer_id++;
        _buffers[id] = buffer;
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

    std::shared_ptr<fixie::buffer> state::buffer(GLuint id)
    {
        auto iter = _buffers.find(id);
        return (iter != end(_buffers)) ? iter->second : nullptr;
    }

    std::shared_ptr<const fixie::buffer> state::buffer(GLuint id) const
    {
        auto iter = _buffers.find(id);
        return (iter != end(_buffers)) ? iter->second : nullptr;
    }

    std::shared_ptr<fixie::buffer>& state::bound_array_buffer()
    {
        return _bound_array_buffer;
    }

    std::shared_ptr<const fixie::buffer> state::bound_array_buffer() const
    {
        return _bound_array_buffer;
    }

    std::shared_ptr<fixie::buffer>& state::bound_element_array_buffer()
    {
        return _bound_element_array_buffer;
    }

    std::shared_ptr<const fixie::buffer> state::bound_element_array_buffer() const
    {
        return _bound_element_array_buffer;
    }
}
