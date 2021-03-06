#ifndef _FIXIE_LIB_CAPS_HPP_
#define _FIXIE_LIB_CAPS_HPP_

#include <vector>
#include <cstddef>

#include "fixie/fixie_gl_types.h"
#include "range.hpp"

namespace fixie
{
    class caps
    {
    public:
        caps();

        GLsizei& max_lights();
        const GLsizei& max_lights() const;

        GLsizei& max_clip_planes();
        const GLsizei& max_clip_planes() const;

        GLsizei& max_model_view_stack_depth();
        const GLsizei& max_model_view_stack_depth() const;

        GLsizei& max_projection_stack_depth();
        const GLsizei& max_projection_stack_depth() const;

        GLsizei& max_texture_stack_depth();
        const GLsizei& max_texture_stack_depth() const;

        GLsizei& subpixel_bits();
        const GLsizei& subpixel_bits() const;

        GLsizei& max_texture_size();
        const GLsizei& max_texture_size() const;

        GLsizei& max_viewport_width();
        const GLsizei& max_viewport_width() const;

        GLsizei& max_viewport_height();
        const GLsizei& max_viewport_height() const;

        range& aliased_point_size_range();
        const range& aliased_point_size_range() const;

        range& smooth_point_size_range();
        const range& smooth_point_size_range() const;

        range& aliased_line_width_range();
        const range& aliased_line_width_range() const;

        range& smooth_line_width_range();
        const range& smooth_line_width_range() const;

        GLsizei& max_texture_units();
        const GLsizei& max_texture_units() const;

        GLsizei& sample_buffers();
        const GLsizei& sample_buffers() const;

        GLsizei& samples();
        const GLsizei& samples() const;

        void insert_compressed_format(GLenum format);
        const GLenum& compressed_format(size_t n) const;
        size_t compressed_format_count() const;

        GLsizei& red_bits();
        const GLsizei& red_bits() const;

        GLsizei& green_bits();
        const GLsizei& green_bits() const;

        GLsizei& blue_bits();
        const GLsizei& blue_bits() const;

        GLsizei& alpha_bits();
        const GLsizei& alpha_bits() const;

        GLsizei& depth_bits();
        const GLsizei& depth_bits() const;

        GLsizei& stencil_bits();
        const GLsizei& stencil_bits() const;

        GLboolean& supports_framebuffer_objects();
        const GLboolean& supports_framebuffer_objects() const;

        GLsizei& max_renderbuffer_size();
        const GLsizei& max_renderbuffer_size() const;

        GLboolean& supports_rgb8_rgba8();
        const GLboolean& supports_rgb8_rgba8() const;

        GLboolean& supports_depth24();
        const GLboolean& supports_depth24() const;

        GLboolean& supports_depth32();
        const GLboolean& supports_depth32() const;

        GLboolean& supports_stencil1();
        const GLboolean& supports_stencil1() const;

        GLboolean& supports_stencil4();
        const GLboolean& supports_stencil4() const;

        GLboolean& supports_stencil8();
        const GLboolean& supports_stencil8() const;

        GLboolean& supports_vertex_array_objects();
        const GLboolean& supports_vertex_array_objects() const;

    private:
        GLsizei _max_lights;
        GLsizei _max_clip_planes;
        GLsizei _max_model_view_stack_depth;
        GLsizei _max_projection_stack_depth;
        GLsizei _max_texture_stack_depth;
        GLsizei _subpixel_bits;
        GLsizei _max_texture_size;
        GLsizei _max_viewport_width;
        GLsizei _max_viewport_height;
        range _aliased_point_size_range;
        range _smooth_point_size_range;
        range _aliased_line_width_range;
        range _smooth_line_width_range;
        GLsizei _max_texture_units;
        GLsizei _sample_buffers;
        GLsizei _samples;
        std::vector<GLenum> _compressed_texture_formats;
        GLsizei _red_bits;
        GLsizei _green_bits;
        GLsizei _blue_bits;
        GLsizei _alpha_bits;
        GLsizei _depth_bits;
        GLsizei _stencil_bits;

        // extensions
        GLboolean _supports_framebuffer_objects;
        GLsizei _max_renderbuffer_size;
        GLboolean _supports_rgb8_rgba8;
        GLboolean _supports_depth24;
        GLboolean _supports_depth32;
        GLboolean _supports_stencil1;
        GLboolean _supports_stencil4;
        GLboolean _supports_stencil8;
        GLboolean _supports_vertex_array_objects;
    };
}

#endif // _FIXIE_LIB_CAPS_HPP_
