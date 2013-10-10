#include "fixie/state.hpp"

#include "fixie/fixie_gl_es.h"
#include "fixie/exceptions.hpp"
#include "fixie/debug.hpp"

namespace fixie
{
    state::state(const caps& caps)
        : _clear_color(0.0f, 0.0f, 0.0f, 0.0f)
        , _clear_depth(1.0f)
        , _clear_stencil(0)
        , _depth_range(0.0f, 1.0f)
        , _depth_func(GL_LESS)
        , _viewport(0, 0, 1, 1)
        , _scissor_test(GL_FALSE)
        , _scissor(0, 0, 1, 1)
        , _front_material(get_default_material())
        , _back_material(get_default_material())
        , _lights(caps.max_lights())
        , _clip_planes(caps.max_clip_planes())
        , _active_texture_unit(0)
        , _matrix_mode(GL_MODELVIEW)
        , _texture_matrix_stacks(caps.max_texture_units())
        , _next_texture_id(1)
        , _bound_textures(caps.max_texture_units())
        , _next_buffer_id(1)
        , _active_client_texture(0)
        , _texcoord_attributes(caps.max_texture_units())
        , _shade_model(GL_SMOOTH)
        , _error(GL_NO_ERROR)
    {
        for (size_t i = 0; i < _lights.size(); i++)
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

    const GLboolean& state::depth_test() const
    {
        return _depth_test;
    }

    GLboolean& state::depth_test()
    {
        return _depth_test;
    }

    range& state::depth_range()
    {
        return _depth_range;
    }

    const range& state::depth_range() const
    {
        return _depth_range;
    }

    GLenum& state::depth_func()
    {
        return _depth_func;
    }

    const GLenum& state::depth_func() const
    {
        return _depth_func;
    }

    rectangle& state::viewport()
    {
        return _viewport;
    }

    const rectangle& state::viewport() const
    {
        return _viewport;
    }

    GLboolean& state::scissor_test()
    {
        return _scissor_test;
    }

    const GLboolean& state::scissor_test() const
    {
        return _scissor_test;
    }

    rectangle& state::scissor()
    {
        return _scissor;
    }

    const rectangle& state::scissor() const
    {
        return _scissor;
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
            for (auto bind = begin(_bound_textures); bind != end(_bound_textures); ++bind)
            {
                if (iter->second == *bind)
                {
                    *bind = nullptr;
                }
            }
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
            if (_bound_array_buffer == iter->second)
            {
                _bound_array_buffer = nullptr;
            }
            if (_bound_element_array_buffer == iter->second)
            {
                _bound_element_array_buffer = nullptr;
            }
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

    void state::bind_array_buffer(std::shared_ptr<fixie::buffer> buf)
    {
        _bound_array_buffer = buf;
        if (buf)
        {
            buf->bind(GL_ARRAY_BUFFER);
            if (_bound_element_array_buffer == buf)
            {
                _bound_element_array_buffer = nullptr;
            }
        }
    }

    std::shared_ptr<const fixie::buffer> state::bound_array_buffer() const
    {
        return _bound_array_buffer;
    }

    std::shared_ptr<fixie::buffer> state::bound_array_buffer()
    {
        return _bound_array_buffer;
    }

    void state::bind_element_array_buffer(std::shared_ptr<fixie::buffer> buf)
    {
        _bound_element_array_buffer = buf;
        if (buf)
        {
            buf->bind(GL_ELEMENT_ARRAY_BUFFER);
            if (_bound_array_buffer == buf)
            {
                _bound_array_buffer = nullptr;
            }
        }
    }

    std::shared_ptr<const fixie::buffer> state::bound_element_array_buffer() const
    {
        return _bound_element_array_buffer;
    }

    std::shared_ptr<fixie::buffer> state::bound_element_array_buffer()
    {
        return _bound_element_array_buffer;
    }

    fixie::vertex_attribute& state::vertex_attribute()
    {
        return _vertex_attribute;
    }

    const fixie::vertex_attribute& state::vertex_attribute() const
    {
        return _vertex_attribute;
    }

    fixie::vertex_attribute& state::normal_attribute()
    {
        return _normal_attribute;
    }

    const fixie::vertex_attribute& state::normal_attribute() const
    {
        return _normal_attribute;
    }

    fixie::vertex_attribute& state::color_attribute()
    {
        return _color_attribute;
    }

    const fixie::vertex_attribute& state::color_attribute() const
    {
        return _color_attribute;
    }

    size_t& state::active_client_texture()
    {
        return _active_client_texture;
    }

    const size_t& state::active_client_texture() const
    {
        return _active_client_texture;
    }

    fixie::vertex_attribute& state::texcoord_attribute(size_t unit)
    {
        return _texcoord_attributes[unit];
    }

    const fixie::vertex_attribute& state::texcoord_attribute(size_t unit) const
    {
        return _texcoord_attributes[unit];
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
