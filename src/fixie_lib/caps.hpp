#ifndef _CAPS_HPP_
#define _CAPS_HPP_

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
        GLboolean _supports_vertex_array_objects;
    };
}

#endif // _CAPS_HPP_
