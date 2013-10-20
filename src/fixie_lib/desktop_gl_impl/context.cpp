#include "fixie_lib/desktop_gl_impl/context.hpp"
#include "fixie_lib/desktop_gl_impl/texture.hpp"
#include "fixie_lib/desktop_gl_impl/buffer.hpp"
#include "fixie_lib/util.hpp"

#include "fixie/fixie_gl_es.h"

#include <assert.h>

namespace fixie
{
    namespace desktop_gl_impl
    {
        void GL_APIENTRY debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message,
                                        const GLvoid* user_param)
        {
            log_message(source, type, id, severity, std::string(message));
        }

        context::context()
            : _functions(std::make_shared<gl_functions>())
            , _shader_cache(_functions)
            , _cur_clear_color(0.0f, 0.0f, 0.0f, 0.0f)
            , _cur_clear_depth(1.0f)
            , _cur_clear_stencil(0)
        {
            initialize_caps(_functions, _caps);

            const GLubyte* gl_version_string = gl_call(_functions, gl_get_string, GL_VERSION);
            _major_version = gl_version_string[0] - '0';
            _minor_version = gl_version_string[2] - '0';

            const GLubyte* gl_renderer_string = gl_call(_functions, gl_get_string, GL_RENDERER);
            const GLubyte* gl_vendor_string = gl_call(_functions, gl_get_string, GL_VENDOR);

            if (_major_version >= 3)
            {
                #define GL_NUM_EXTENSIONS 0x821D

                GLint num_extensions;
                gl_call(_functions, gl_get_integerv, GL_NUM_EXTENSIONS, &num_extensions);
                for (GLint i = 0; i < num_extensions; i++)
                {
                    const GLubyte* extension_name = gl_call(_functions, gl_get_stringi, GL_EXTENSIONS, i);
                    _extensions.insert(reinterpret_cast<const char*>(extension_name));
                }
            }
            else
            {
                const GLubyte* gl_extension_string = gl_call(_functions, gl_get_string, GL_EXTENSIONS);
                split(reinterpret_cast<const char*>(gl_extension_string), ' ', std::inserter(_extensions, _extensions.end()));
            }

            _renderer_string = format("%s OpenGL %s", reinterpret_cast<const char*>(gl_renderer_string), reinterpret_cast<const char*>(gl_version_string));

            if (_extensions.find("GL_ARB_debug_output") != end(_extensions))
            {
                gl_call(_functions, gl_enable, GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
                gl_call(_functions, gl_debug_message_control_arb, GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_MEDIUM_ARB, 0, nullptr, GL_TRUE);
                gl_call(_functions, gl_debug_message_callback_arb, debug_callback, nullptr);
            }
        }

        const fixie::caps& context::caps()
        {
            return _caps;
        }

        const std::string& context::renderer_desc()
        {
            return _renderer_string;
        }

        void context::initialize_state(fixie::state& state)
        {
            GLint viewport_values[4];
            gl_call(_functions, gl_get_integerv, GL_VIEWPORT, viewport_values);
            state.viewport() = rectangle(viewport_values[0], viewport_values[1], viewport_values[2], viewport_values[3]);

            GLint scissor_values[4];
            gl_call(_functions, gl_get_integerv, GL_SCISSOR_BOX, scissor_values);
            state.scissor() = rectangle(scissor_values[0], scissor_values[1], scissor_values[2], scissor_values[3]);
        }

        std::shared_ptr<texture_impl> context::create_texture()
        {
            return std::make_shared<texture>(_functions);
        }

        std::shared_ptr<buffer_impl> context::create_buffer()
        {
            return std::make_shared<buffer>(_functions);
        }

        void context::draw_arrays(const state& state, GLenum mode, GLint first, GLsizei count)
        {
            std::shared_ptr<shader> shader = _shader_cache.get_shader(state, _caps);
            shader->sync_state(state);
            sync_vertex_attributes(state, shader);
            sync_textures(state);

            gl_call(_functions, gl_draw_arrays, mode, first, count);
        }

        void context::draw_elements(const state& state, GLenum mode, GLsizei count, GLenum type, const GLvoid* indices)
        {
            std::shared_ptr<shader> shader = _shader_cache.get_shader(state, _caps);
            shader->sync_state(state);
            sync_vertex_attributes(state, shader);
            sync_textures(state);

            gl_call(_functions, gl_draw_elements, mode, count, type, indices);
        }

        void context::clear(const state& state, GLbitfield mask)
        {
            sync_clear_state(state);
            sync_rasterizer_state(state);
            gl_call(_functions, gl_clear, mask);
        }

        void context::sync_clear_state(const state& state)
        {
            if (_cur_clear_color != state.clear_color())
            {
                gl_call(_functions, gl_clear_color, state.clear_color().r, state.clear_color().g, state.clear_color().b, state.clear_color().a);
                _cur_clear_color = state.clear_color();
            }

            if (_cur_clear_depth != state.clear_depth())
            {
                gl_call(_functions, gl_clear_depthf, state.clear_depth());
                _cur_clear_depth = state.clear_depth();
            }

            if (_cur_clear_stencil != state.clear_stencil())
            {
                gl_call(_functions, gl_clear_stencil, state.clear_stencil());
                _cur_clear_stencil = state.clear_stencil();
            }
        }

        void context::sync_rasterizer_state(const state& state)
        {
            if (_cur_scissor_test != state.scissor_test())
            {
                if (state.scissor_test())
                {
                    gl_call(_functions, gl_enable, GL_SCISSOR_TEST);
                }
                else
                {
                    gl_call(_functions, gl_disable, GL_SCISSOR_TEST);
                }
                _cur_scissor_test = state.scissor_test();
            }

            if (_cur_scissor != state.scissor())
            {
                gl_call(_functions, gl_scissor, state.scissor().x, state.scissor().y, state.scissor().width, state.scissor().height);
                _cur_scissor = state.scissor();
            }

            if (_cur_viewport != state.viewport())
            {
                gl_call(_functions, gl_viewport, state.viewport().x, state.viewport().y, state.viewport().width, state.viewport().height);
                _cur_viewport = state.viewport();
            }
        }

        void context::sync_vertex_attribute(const state& state, const vertex_attribute& attribute, GLuint location, GLboolean normalized)
        {
            if (attribute.enabled())
            {
                std::shared_ptr<const buffer> bound_buffer = std::dynamic_pointer_cast<const buffer>(attribute.buffer()->impl());

                gl_call(_functions, gl_bind_buffer, GL_ARRAY_BUFFER, bound_buffer->id());
                gl_call(_functions, gl_enable_vertex_attrib_array, location);
                gl_call(_functions, gl_vertex_attrib_pointer, location, attribute.size(), attribute.type(), normalized, attribute.stride(), attribute.pointer());
            }
            else
            {
                const vector4& generic_values = attribute.generic_values();

                gl_call(_functions, gl_bind_buffer, GL_ARRAY_BUFFER, 0);
                gl_call(_functions, gl_disable_vertex_attrib_array, location);
                gl_call(_functions, gl_vertex_attrib_4f, location, generic_values.x, generic_values.y, generic_values.z, generic_values.w);
            }
        }

        void context::sync_vertex_attributes(const state& state, std::shared_ptr<const shader> shader)
        {
            GLint vertex_location = shader->vertex_attribute_location();
            if (vertex_location != -1)
            {
                sync_vertex_attribute(state, state.vertex_attribute(), static_cast<GLuint>(vertex_location), GL_FALSE);
            }

            GLint color_location = shader->color_attribute_location();
            if (color_location != -1)
            {
                sync_vertex_attribute(state, state.color_attribute(), static_cast<GLuint>(color_location), GL_TRUE);
            }

            GLint normal_location = shader->normal_attribute_location();
            if (normal_location != -1)
            {
                sync_vertex_attribute(state, state.normal_attribute(), static_cast<GLuint>(normal_location), GL_TRUE);
            }

            for (size_t i = 0; i < static_cast<size_t>(_caps.max_texture_units()); ++i)
            {
                GLint texcoord_location = shader->texcoord_attribute_location(i);
                if (texcoord_location != -1)
                {
                    sync_vertex_attribute(state, state.texcoord_attribute(i), static_cast<GLuint>(texcoord_location), GL_TRUE);
                }
            }
        }

        void context::sync_textures(const state& state)
        {
            for (size_t i = 0; i < static_cast<size_t>(_caps.max_texture_units()); ++i)
            {
                if (state.texture_environment(i).enabled())
                {
                    std::shared_ptr<const fixie::texture> bound_texture = state.bound_texture(i);
                    GLuint texuture_id = bound_texture ? std::dynamic_pointer_cast<const texture>(bound_texture->impl())->id() : 0;

                    gl_call(_functions, gl_active_texture, GL_TEXTURE0 + i);
                    gl_call(_functions, gl_enable, GL_TEXTURE_2D);
                    gl_call(_functions, gl_bind_texture, GL_TEXTURE_2D, texuture_id);
                }
            }
        }

        void context::initialize_caps(std::shared_ptr<const gl_functions> functions, fixie::caps& caps)
        {
            caps.max_lights() = 8;
            caps.max_clip_planes() = 6;
            caps.max_model_view_stack_depth() = 1024;
            caps.max_projection_stack_depth() = 1024;
            caps.max_texture_stack_depth() = 1024;
            gl_call(functions, gl_get_integerv, GL_SUBPIXEL_BITS, &caps.subpixel_bits());
            gl_call(functions, gl_get_integerv, GL_MAX_TEXTURE_SIZE, &caps.max_texture_size());

            GLint max_viewport_dims[2];
            gl_call(functions, gl_get_integerv, GL_MAX_VIEWPORT_DIMS, max_viewport_dims);
            caps.max_viewport_width() = max_viewport_dims[0];
            caps.max_viewport_height() = max_viewport_dims[1];

            #define GL_POINT_SIZE_RANGE 0x0B12
            GLfloat point_point_size_range_values[2];
            gl_call(functions, gl_get_floatv, GL_POINT_SIZE_RANGE, point_point_size_range_values);
            caps.aliased_point_size_range() = range(point_point_size_range_values[0], point_point_size_range_values[1]);
            caps.smooth_point_size_range() = range(point_point_size_range_values[0], point_point_size_range_values[1]);

            GLfloat aliased_line_width_range_values[2];
            gl_call(functions, gl_get_floatv, GL_ALIASED_LINE_WIDTH_RANGE, aliased_line_width_range_values);
            caps.aliased_line_width_range() = range(aliased_line_width_range_values[0], aliased_line_width_range_values[1]);

            GLfloat smooth_line_width_range_values[2];
            gl_call(functions, gl_get_floatv, GL_SMOOTH_LINE_WIDTH_RANGE, smooth_line_width_range_values);
            caps.smooth_line_width_range() = range(smooth_line_width_range_values[0], smooth_line_width_range_values[1]);

            gl_call(functions, gl_get_integerv, GL_MAX_TEXTURE_UNITS, &caps.max_texture_units());
            gl_call(functions, gl_get_integerv, GL_SAMPLE_BUFFERS, &caps.sample_buffers());
            gl_call(functions, gl_get_integerv, GL_SAMPLES, &caps.samples());

            GLint compressed_format_count;
            gl_call(functions, gl_get_integerv, GL_NUM_COMPRESSED_TEXTURE_FORMATS, &compressed_format_count);

            std::vector<GLint> compressed_formats(compressed_format_count);
            gl_call(functions, gl_get_integerv, GL_COMPRESSED_TEXTURE_FORMATS, compressed_formats.data());
            for (GLint i = 0; i < compressed_format_count; ++i)
            {
                caps.insert_compressed_format(compressed_formats[i]);
            }
            
            gl_call(functions, gl_get_integerv, GL_RED_BITS, &caps.red_bits());
            gl_call(functions, gl_get_integerv, GL_GREEN_BITS, &caps.green_bits());
            gl_call(functions, gl_get_integerv, GL_BLUE_BITS, &caps.blue_bits());
            gl_call(functions, gl_get_integerv, GL_ALPHA_BITS, &caps.alpha_bits());
            gl_call(functions, gl_get_integerv, GL_DEPTH_BITS, &caps.depth_bits());
            gl_call(functions, gl_get_integerv, GL_STENCIL_BITS, &caps.stencil_bits());
        }
    }
}
