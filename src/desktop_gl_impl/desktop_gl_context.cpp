#include "desktop_gl_impl/desktop_gl_context.hpp"
#include "desktop_gl_impl/desktop_gl_texture.hpp"
#include "desktop_gl_impl/desktop_gl_buffer.hpp"

#include "fixie_gl_es.h"

namespace fixie
{
    namespace desktop_gl_impl
    {
        context::context()
            : _cur_clear_color(0.0f, 0.0f, 0.0f, 0.0f)
            , _cur_clear_depth(1.0f)
            , _cur_clear_stencil(0)
        {
            initialize_caps(_functions, _caps);
        }

        const fixie::caps& context::caps()
        {
            return _caps;
        }

        void context::initialize_state(fixie::state& state)
        {
            GLint viewport_values[4];
            _functions.gl_get_integerv()(GL_VIEWPORT, viewport_values);
            state.viewport() = rectangle(viewport_values[0], viewport_values[1], viewport_values[2], viewport_values[3]);

            GLint scissor_values[4];
            _functions.gl_get_integerv()(GL_SCISSOR_BOX, scissor_values);
            state.scissor() = rectangle(scissor_values[0], scissor_values[1], scissor_values[2], scissor_values[3]);
        }

        std::shared_ptr<texture_impl> context::create_texture()
        {
            return std::make_shared<texture>();
        }

        std::shared_ptr<buffer_impl> context::create_buffer()
        {
            return std::make_shared<buffer>();
        }

        void context::draw_arrays(const state& state, GLenum mode, GLint first, GLsizei count)
        {
        }

        void context::draw_elements(const state& state, GLenum mode, GLsizei count, GLenum type, GLvoid* indices)
        {
        }

        void context::clear(const state& state, GLbitfield mask)
        {
            sync_clear_state(state);
            sync_rasterizer_state(state);
            _functions.gl_clear()(mask);
        }

        void context::sync_clear_state(const state& state)
        {
            if (_cur_clear_color != state.clear_color())
            {
                _functions.gl_clear_color()(state.clear_color().r, state.clear_color().g, state.clear_color().b, state.clear_color().a);
                _cur_clear_color = state.clear_color();
            }

            if (_cur_clear_depth != state.clear_depth())
            {
                _functions.gl_clear_depthf()(state.clear_depth());
                _cur_clear_depth = state.clear_depth();
            }

            if (_cur_clear_stencil != state.clear_stencil())
            {
                _functions.gl_clear_stencil()(state.clear_stencil());
                _cur_clear_stencil = state.clear_stencil();
            }
        }

        void context::sync_rasterizer_state(const state& state)
        {
            if (_cur_scissor_test != state.scissor_test())
            {
                if (state.scissor_test())
                {
                    _functions.gl_enable()(GL_SCISSOR_TEST);
                }
                else
                {
                    _functions.gl_disable()(GL_SCISSOR_TEST);
                }
                _cur_scissor_test = state.scissor_test();
            }

            if (_cur_scissor != state.scissor())
            {
                _functions.gl_scissor()(state.scissor().x, state.scissor().y, state.scissor().width, state.scissor().height);
                _cur_scissor = state.scissor();
            }

            if (_cur_viewport != state.viewport())
            {
                _functions.gl_viewport()(state.viewport().x, state.viewport().y, state.viewport().width, state.viewport().height);
                _cur_viewport = state.viewport();
            }
        }

        void context::initialize_caps(const gl_functions& functions, fixie::caps& caps)
        {
            caps.max_lights() = 8;
            caps.max_clip_planes() = 6;
            caps.max_model_view_stack_depth() = 1024;
            caps.max_projection_stack_depth() = 1024;
            caps.max_texture_stack_depth() = 1024;
            functions.gl_get_integerv()(GL_SUBPIXEL_BITS, &caps.subpixel_bits());
            functions.gl_get_integerv()(GL_MAX_TEXTURE_SIZE, &caps.max_texture_size());

            GLint max_viewport_dims[2];
            functions.gl_get_integerv()(GL_MAX_VIEWPORT_DIMS, max_viewport_dims);
            caps.max_viewport_width() = max_viewport_dims[0];
            caps.max_viewport_height() = max_viewport_dims[1];

            #define GL_POINT_SIZE_RANGE 0x0B12
            GLfloat point_point_size_range_values[2];
            functions.gl_get_floatv()(GL_POINT_SIZE_RANGE, point_point_size_range_values);
            caps.aliased_point_size_range() = range(point_point_size_range_values[0], point_point_size_range_values[1]);
            caps.smooth_point_size_range() = range(point_point_size_range_values[0], point_point_size_range_values[1]);

            GLfloat aliased_line_width_range_values[2];
            functions.gl_get_floatv()(GL_ALIASED_LINE_WIDTH_RANGE, aliased_line_width_range_values);
            caps.aliased_line_width_range() = range(aliased_line_width_range_values[0], aliased_line_width_range_values[1]);

            GLfloat smooth_line_width_range_values[2];
            functions.gl_get_floatv()(GL_SMOOTH_LINE_WIDTH_RANGE, smooth_line_width_range_values);
            caps.smooth_line_width_range() = range(smooth_line_width_range_values[0], smooth_line_width_range_values[1]);

            functions.gl_get_integerv()(GL_MAX_TEXTURE_UNITS, &caps.max_texture_units());
            functions.gl_get_integerv()(GL_SAMPLE_BUFFERS, &caps.sample_buffers());
            functions.gl_get_integerv()(GL_SAMPLES, &caps.samples());

            GLint compressed_format_count;
            functions.gl_get_integerv()(GL_NUM_COMPRESSED_TEXTURE_FORMATS, &compressed_format_count);

            std::vector<GLint> compressed_formats(compressed_format_count);
            functions.gl_get_integerv()(GL_COMPRESSED_TEXTURE_FORMATS, compressed_formats.data());
            for (GLint i = 0; i < compressed_format_count; ++i)
            {
                caps.insert_compressed_format(compressed_formats[i]);
            }
            
            functions.gl_get_integerv()(GL_RED_BITS, &caps.red_bits());
            functions.gl_get_integerv()(GL_GREEN_BITS, &caps.green_bits());
            functions.gl_get_integerv()(GL_BLUE_BITS, &caps.blue_bits());
            functions.gl_get_integerv()(GL_ALPHA_BITS, &caps.alpha_bits());
            functions.gl_get_integerv()(GL_DEPTH_BITS, &caps.depth_bits());
            functions.gl_get_integerv()(GL_STENCIL_BITS, &caps.stencil_bits());
        }
    }
}
