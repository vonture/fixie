#include "fixie_lib/desktop_gl_impl/context.hpp"
#include "fixie_lib/desktop_gl_impl/texture.hpp"
#include "fixie_lib/desktop_gl_impl/framebuffer.hpp"
#include "fixie_lib/desktop_gl_impl/buffer.hpp"
#include "fixie_lib/desktop_gl_impl/exceptions.hpp"
#include "fixie_lib/util.hpp"

#include "fixie/fixie_gl_es.h"

#include <assert.h>

namespace fixie
{
    namespace desktop_gl_impl
    {
        #define GL_FRAMEBUFFER 0x8D40

        void FIXIE_APIENTRY debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                                           const GLchar* message, GLvoid* user_aram)
        {
            log_message(source, type, id, severity, std::string(message));
        }

        context::context()
            : _functions(std::make_shared<gl_functions>())
            , _version(initialize_version(_functions))
            , _caps(initialize_caps(_functions, _version))
            , _shader_cache(_functions)
            , _cur_depth_stencil_state(get_default_depth_stencil_state())
            , _cur_clear_state(get_default_clear_state())
            , _cur_rasterizer_state(get_default_rasterizer_state())
            , _vao(0)
        {
            const GLubyte* gl_renderer_string = gl_call(_functions, get_string, GL_RENDERER);
            const GLubyte* gl_vendor_string = gl_call(_functions, get_string, GL_VENDOR);

            if (_version >= gl_3_0 || _version >= gl_es_3_0)
            {
                #define GL_NUM_EXTENSIONS 0x821D

                GLint num_extensions;
                gl_call(_functions, get_integer_v, GL_NUM_EXTENSIONS, &num_extensions);
                for (GLint i = 0; i < num_extensions; i++)
                {
                    const GLubyte* extension_name = gl_call(_functions, get_string_i, GL_EXTENSIONS, i);
                    _extensions.insert(reinterpret_cast<const char*>(extension_name));
                }
            }
            else
            {
                const GLubyte* gl_extension_string = gl_call(_functions, get_string, GL_EXTENSIONS);
                split(reinterpret_cast<const char*>(gl_extension_string), ' ', std::inserter(_extensions, _extensions.end()));
            }

            _renderer_string = format("%s OpenGL %s", reinterpret_cast<const char*>(gl_renderer_string), _version.str().c_str());

            if (_version >= gl_4_3 || _extensions.find("GL_KHR_debug") != end(_extensions))
            {
                gl_call(_functions, enable, GL_DEBUG_OUTPUT_SYNCHRONOUS);
                gl_call(_functions, debug_message_control, GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_MEDIUM, 0, nullptr, GL_TRUE);
                gl_call(_functions, debug_message_callback, debug_callback, this);
            }

            if (_version >= gl_3_0 || _version >= gl_es_3_0 || _extensions.find("GL_ARB_vertex_array_object") != end(_extensions))
            {
                // need to generate a vao to use so 0 it not bound
                gl_call(_functions, gen_vertex_arrays, 1, &_vao);
                gl_call(_functions, bind_vertex_array, _vao)
            }
        }

        context::~context()
        {
            if (_vao != 0)
            {
                gl_call_nothrow(_functions, delete_vertex_arrays, 1, &_vao);
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
            gl_call(_functions, get_integer_v, GL_VIEWPORT, viewport_values);
            state.rasterizer_state().viewport() = rectangle(viewport_values[0], viewport_values[1], viewport_values[2], viewport_values[3]);

            GLint scissor_values[4];
            gl_call(_functions, get_integer_v, GL_SCISSOR_BOX, scissor_values);
            state.rasterizer_state().scissor() = rectangle(scissor_values[0], scissor_values[1], scissor_values[2], scissor_values[3]);
        }

        std::unique_ptr<texture_impl> context::create_texture()
        {
            return std::unique_ptr<texture_impl>(new texture(_functions));
        }

        std::unique_ptr<framebuffer_impl> context::create_default_framebuffer()
        {
            return std::unique_ptr<framebuffer_impl>(new default_framebuffer(_functions));
        }

        std::unique_ptr<framebuffer_impl> context::create_framebuffer()
        {
            return std::unique_ptr<framebuffer_impl>(new framebuffer(_functions));
        }

        std::unique_ptr<buffer_impl> context::create_buffer()
        {
            return std::unique_ptr<buffer_impl>(new buffer(_functions));
        }

        void context::draw_arrays(const state& state, GLenum mode, GLint first, GLsizei count)
        {
            sync_draw_state(state);

            gl_call(_functions, draw_arrays, mode, first, count);
        }

        void context::draw_elements(const state& state, GLenum mode, GLsizei count, GLenum type, const GLvoid* indices)
        {
            sync_draw_state(state);

            gl_call(_functions, draw_elements, mode, count, type, indices);
        }

        void context::clear(const state& state, GLbitfield mask)
        {
            sync_clear_state(state.clear_state());
            sync_rasterizer_state(state.rasterizer_state());
            sync_framebuffer(state);
            gl_call(_functions, clear, mask);
        }

        void context::sync_depth_stencil_state(const depth_stencil_state& state)
        {
            if (_cur_depth_stencil_state.depth_func() != state.depth_func())
            {
                gl_call(_functions, depth_func, state.depth_func());
                _cur_depth_stencil_state.depth_func() = state.depth_func();
            }

            if (_cur_depth_stencil_state.depth_test() != state.depth_test())
            {
                if (state.depth_test())
                {
                    gl_call(_functions, enable, GL_DEPTH_TEST);
                }
                else
                {
                    gl_call(_functions, disable, GL_DEPTH_TEST);
                }
                _cur_depth_stencil_state.depth_test() = state.depth_test();
            }

            if (_cur_depth_stencil_state.depth_mask() != state.depth_mask())
            {
                gl_call(_functions, depth_mask, state.depth_mask());
                _cur_depth_stencil_state.depth_mask() = state.depth_mask();
            }

            if (_cur_depth_stencil_state.depth_range() != state.depth_range())
            {
                gl_call(_functions, depth_range_f, state.depth_range().near, state.depth_range().far);
                _cur_depth_stencil_state.depth_range() = state.depth_range();
            }

            if (_cur_depth_stencil_state.stencil_func() != state.stencil_func() ||
                _cur_depth_stencil_state.stencil_ref() != state.stencil_ref() ||
                _cur_depth_stencil_state.stencil_mask() != state.stencil_mask())
            {
                gl_call(_functions, stencil_func, state.stencil_func(), state.stencil_ref(), state.stencil_mask());
                _cur_depth_stencil_state.stencil_func() = state.stencil_func();
                _cur_depth_stencil_state.stencil_ref() = state.stencil_ref();
                _cur_depth_stencil_state.stencil_mask() = state.stencil_mask();
            }

            if (_cur_depth_stencil_state.stencil_fail_operation() != state.stencil_fail_operation() ||
                _cur_depth_stencil_state.stencil_pass_depth_fail_operation() != state.stencil_pass_depth_fail_operation() ||
                _cur_depth_stencil_state.stencil_pass_depth_pass_operation() != state.stencil_pass_depth_pass_operation())
            {
                gl_call(_functions, stencil_op, state.stencil_fail_operation(), state.stencil_pass_depth_fail_operation(),
                                                state.stencil_pass_depth_pass_operation());
                _cur_depth_stencil_state.stencil_fail_operation() = state.stencil_fail_operation();
                _cur_depth_stencil_state.stencil_pass_depth_fail_operation() = state.stencil_pass_depth_fail_operation();
                _cur_depth_stencil_state.stencil_pass_depth_pass_operation() = state.stencil_pass_depth_pass_operation();
            }
        }

        void context::sync_clear_state(const clear_state& state)
        {
            if (_cur_clear_state.clear_color() != state.clear_color())
            {
                gl_call(_functions, clear_color, state.clear_color().r(), state.clear_color().g(), state.clear_color().b(), state.clear_color().a());
                _cur_clear_state.clear_color() = state.clear_color();
            }

            if (_cur_clear_state.clear_depth() != state.clear_depth())
            {
                gl_call(_functions, clear_depthf, state.clear_depth());
                _cur_clear_state.clear_depth() = state.clear_depth();
            }

            if (_cur_clear_state.clear_stencil() != state.clear_stencil())
            {
                gl_call(_functions, clear_stencil, state.clear_stencil());
                _cur_clear_state.clear_stencil() = state.clear_stencil();
            }
        }

        void context::sync_rasterizer_state(const rasterizer_state& state)
        {
            if (_cur_rasterizer_state.scissor_test() != state.scissor_test())
            {
                if (state.scissor_test())
                {
                    gl_call(_functions, enable, GL_SCISSOR_TEST);
                }
                else
                {
                    gl_call(_functions, disable, GL_SCISSOR_TEST);
                }
                _cur_rasterizer_state.scissor_test() = state.scissor_test();
            }

            if (_cur_rasterizer_state.scissor() != state.scissor())
            {
                gl_call(_functions, scissor, state.scissor().x, state.scissor().y, state.scissor().width, state.scissor().height);
                _cur_rasterizer_state.scissor() = state.scissor();
            }

            if (_cur_rasterizer_state.viewport() != state.viewport())
            {
                gl_call(_functions, viewport, state.viewport().x, state.viewport().y, state.viewport().width, state.viewport().height);
                _cur_rasterizer_state.viewport() = state.viewport();
            }
        }

        void context::sync_vertex_attribute(const state& state, const vertex_attribute& attribute, GLint location, GLboolean normalized)
        {
            if (location != -1)
            {
                if (attribute.enabled())
                {
                    std::shared_ptr<const fixie::buffer> bound_buffer = attribute.buffer().lock();
                    std::shared_ptr<const fixie::buffer_impl> bound_buffer_impl = (bound_buffer != nullptr) ? bound_buffer->impl().lock() : nullptr;
                    std::shared_ptr<const buffer> desktop_buffer = std::dynamic_pointer_cast<const buffer>(bound_buffer_impl);
                    GLuint buffer_id = desktop_buffer ? desktop_buffer->id() : 0;

                    gl_call(_functions, bind_buffer, GL_ARRAY_BUFFER, buffer_id);
                    gl_call(_functions, enable_vertex_attrib_array, location);
                    gl_call(_functions, vertex_attrib_pointer, location, attribute.size(), attribute.type(), normalized, attribute.stride(), attribute.pointer());
                }
                else
                {
                    const vector4& generic_values = attribute.generic_values();

                    gl_call(_functions, bind_buffer, GL_ARRAY_BUFFER, 0);
                    gl_call(_functions, disable_vertex_attrib_array, location);
                    gl_call(_functions, vertex_attrib_4f, location, generic_values.x(), generic_values.y(), generic_values.z(), generic_values.w());
                }
            }
        }

        void context::sync_vertex_attributes(const state& state, std::weak_ptr<const shader> shader)
        {
            std::shared_ptr<const desktop_gl_impl::shader> locked_shader = shader.lock();
            assert(locked_shader != nullptr);

            sync_vertex_attribute(state, state.vertex_attribute(), locked_shader->vertex_attribute_location(), GL_FALSE);
            sync_vertex_attribute(state, state.color_attribute(), locked_shader->color_attribute_location(), GL_TRUE);
            sync_vertex_attribute(state, state.normal_attribute(), locked_shader->normal_attribute_location(), GL_TRUE);
            for (size_t i = 0; i < static_cast<size_t>(_caps.max_texture_units()); ++i)
            {
                sync_vertex_attribute(state, state.texcoord_attribute(i), locked_shader->texcoord_attribute_location(i), GL_TRUE);
            }
        }

        void context::sync_textures(const state& state)
        {
            for (size_t i = 0; i < static_cast<size_t>(_caps.max_texture_units()); ++i)
            {
                if (state.texture_environment(i).enabled())
                {
                    std::shared_ptr<const fixie::texture> bound_texture = state.bound_texture(i).lock();
                    std::shared_ptr<const fixie::texture_impl> bound_texture_impl = (bound_texture != nullptr) ? bound_texture->impl().lock() : nullptr;
                    std::shared_ptr<const texture> desktop_texture = std::dynamic_pointer_cast<const texture>(bound_texture_impl);
                    GLuint texuture_id = desktop_texture ? desktop_texture->id() : 0;

                    gl_call(_functions, active_texture, static_cast<GLenum>(GL_TEXTURE0 + i));
                    gl_call(_functions, enable, GL_TEXTURE_2D);
                    gl_call(_functions, bind_texture, GL_TEXTURE_2D, texuture_id);
                    if (bound_texture)
                    {
                        gl_call(_functions, tex_parameter_i, GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, bound_texture->wrap_s());
                        gl_call(_functions, tex_parameter_i, GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, bound_texture->wrap_t());
                        gl_call(_functions, tex_parameter_i, GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, bound_texture->min_filter());
                        gl_call(_functions, tex_parameter_i, GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, bound_texture->mag_filter());
                    }
                }
            }
        }

        void context::sync_framebuffer(const state& state)
        {
            std::shared_ptr<const fixie::framebuffer> bound_framebuffer = state.bound_draw_framebuffer().lock();
            std::shared_ptr<const fixie::framebuffer_impl> bound_framebuffer_impl = bound_framebuffer ? bound_framebuffer->impl().lock() : nullptr;
            std::shared_ptr<const framebuffer> desktop_framebuffer = std::dynamic_pointer_cast<const framebuffer>(bound_framebuffer_impl);
            GLuint framebuffer_id = desktop_framebuffer ? desktop_framebuffer->id() : 0;

            gl_call(_functions, bind_framebuffer, GL_FRAMEBUFFER, framebuffer_id);
        }

        void context::sync_draw_state(const state& state)
        {
            std::shared_ptr<shader> shader = _shader_cache.get_shader(state, _caps).lock();
            shader->sync_state(state);
            sync_vertex_attributes(state, shader);
            sync_textures(state);
            sync_framebuffer(state);
            sync_depth_stencil_state(state.depth_stencil_state());
            sync_rasterizer_state(state.rasterizer_state());
        }

        gl_version context::initialize_version(std::shared_ptr<const gl_functions> functions)
        {
            const GLubyte* gl_version_string = gl_call(functions, get_string, GL_VERSION);
            return gl_version(std::string(reinterpret_cast<const char*>(gl_version_string)));
        }

        fixie::caps context::initialize_caps(std::shared_ptr<const gl_functions> functions,  const gl_version version)
        {
            fixie::caps caps;

            caps.max_lights() = 8;
            caps.max_clip_planes() = 6;
            caps.max_model_view_stack_depth() = 1024;
            caps.max_projection_stack_depth() = 1024;
            caps.max_texture_stack_depth() = 1024;
            gl_call(functions, get_integer_v, GL_SUBPIXEL_BITS, &caps.subpixel_bits());
            gl_call(functions, get_integer_v, GL_MAX_TEXTURE_SIZE, &caps.max_texture_size());

            GLint max_viewport_dims[2];
            gl_call(functions, get_integer_v, GL_MAX_VIEWPORT_DIMS, max_viewport_dims);
            caps.max_viewport_width() = max_viewport_dims[0];
            caps.max_viewport_height() = max_viewport_dims[1];

            #define GL_POINT_SIZE_RANGE 0x0B12
            GLfloat point_point_size_range_values[2];
            gl_call(functions, get_float_v, GL_POINT_SIZE_RANGE, point_point_size_range_values);
            caps.aliased_point_size_range() = range(point_point_size_range_values[0], point_point_size_range_values[1]);
            caps.smooth_point_size_range() = range(point_point_size_range_values[0], point_point_size_range_values[1]);

            GLfloat aliased_line_width_range_values[2];
            gl_call(functions, get_float_v, GL_ALIASED_LINE_WIDTH_RANGE, aliased_line_width_range_values);
            caps.aliased_line_width_range() = range(aliased_line_width_range_values[0], aliased_line_width_range_values[1]);

            GLfloat smooth_line_width_range_values[2];
            gl_call(functions, get_float_v, GL_SMOOTH_LINE_WIDTH_RANGE, smooth_line_width_range_values);
            caps.smooth_line_width_range() = range(smooth_line_width_range_values[0], smooth_line_width_range_values[1]);

            gl_call(functions, get_integer_v, GL_MAX_TEXTURE_UNITS, &caps.max_texture_units());
            gl_call(functions, get_integer_v, GL_SAMPLE_BUFFERS, &caps.sample_buffers());
            gl_call(functions, get_integer_v, GL_SAMPLES, &caps.samples());

            GLint compressed_format_count;
            gl_call(functions, get_integer_v, GL_NUM_COMPRESSED_TEXTURE_FORMATS, &compressed_format_count);

            std::vector<GLint> compressed_formats(compressed_format_count);
            gl_call(functions, get_integer_v, GL_COMPRESSED_TEXTURE_FORMATS, compressed_formats.data());
            for (GLint i = 0; i < compressed_format_count; ++i)
            {
                caps.insert_compressed_format(compressed_formats[i]);
            }

            if (version >= gl_3_0 || version >= gl_es_3_0)
            {
                #define GL_FRONT_LEFT 0x0400
                #define GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE 0x8212
                #define GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE 0x8213
                #define GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE 0x8214
                #define GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE 0x8215
                #define GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE 0x8216
                #define GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE 0x8217
                #define GL_DEPTH 0x1801
                #define GL_STENCIL 0x1802

                gl_call(functions, get_framebuffer_attachment_parameter_iv, GL_FRAMEBUFFER, GL_FRONT_LEFT, GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE, &caps.red_bits());
                gl_call(functions, get_framebuffer_attachment_parameter_iv, GL_FRAMEBUFFER, GL_FRONT_LEFT, GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE, &caps.green_bits());
                gl_call(functions, get_framebuffer_attachment_parameter_iv, GL_FRAMEBUFFER, GL_FRONT_LEFT, GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE, &caps.blue_bits());
                gl_call(functions, get_framebuffer_attachment_parameter_iv, GL_FRAMEBUFFER, GL_FRONT_LEFT, GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE, &caps.alpha_bits());
                gl_call(functions, get_framebuffer_attachment_parameter_iv, GL_FRAMEBUFFER, GL_DEPTH, GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE, &caps.depth_bits());
                gl_call(functions, get_framebuffer_attachment_parameter_iv, GL_FRAMEBUFFER, GL_STENCIL, GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE, &caps.stencil_bits());
            }
            else
            {
                gl_call(functions, get_integer_v, GL_RED_BITS, &caps.red_bits());
                gl_call(functions, get_integer_v, GL_GREEN_BITS, &caps.green_bits());
                gl_call(functions, get_integer_v, GL_BLUE_BITS, &caps.blue_bits());
                gl_call(functions, get_integer_v, GL_ALPHA_BITS, &caps.alpha_bits());
                gl_call(functions, get_integer_v, GL_DEPTH_BITS, &caps.depth_bits());
                gl_call(functions, get_integer_v, GL_STENCIL_BITS, &caps.stencil_bits());
            }

            return caps;
        }
    }
}
