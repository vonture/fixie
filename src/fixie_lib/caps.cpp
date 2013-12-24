#include "fixie_lib/caps.hpp"

#include <algorithm>

namespace fixie
{
    caps::caps()
        : _max_lights(0)
        , _max_clip_planes(0)
        , _max_model_view_stack_depth(0)
        , _max_projection_stack_depth(0)
        , _max_texture_stack_depth(0)
        , _subpixel_bits(0)
        , _max_texture_size(0)
        , _max_viewport_width(0)
        , _max_viewport_height(0)
        , _aliased_point_size_range(0.0f, 0.0f)
        , _smooth_point_size_range(0.0f, 0.0f)
        , _aliased_line_width_range(0.0f, 0.0f)
        , _smooth_line_width_range(0.0f, 0.0f)
        , _max_texture_units(0)
        , _sample_buffers(0)
        , _samples(0)
        , _red_bits(0)
        , _green_bits(0)
        , _blue_bits(0)
        , _alpha_bits(0)
        , _depth_bits(0)
        , _stencil_bits(0)
        , _supports_framebuffer_objects(0)
        , _max_renderbuffer_size(0)
        , _supports_rgb8_rgba8(0)
        , _supports_depth24(0)
        , _supports_depth32(0)
        , _supports_stencil1(0)
        , _supports_stencil4(0)
        , _supports_stencil8(0)
        , _supports_vertex_array_objects(0)
    {
    }

    GLsizei& caps::max_lights()
    {
        return _max_lights;
    }

    const GLsizei& caps::max_lights() const
    {
        return _max_lights;
    }

    GLsizei& caps::max_clip_planes()
    {
        return _max_clip_planes;
    }

    const GLsizei& caps::max_clip_planes() const
    {
        return _max_clip_planes;
    }

    GLsizei& caps::max_model_view_stack_depth()
    {
        return _max_model_view_stack_depth;
    }

    const GLsizei& caps::max_model_view_stack_depth() const
    {
        return _max_model_view_stack_depth;
    }

    GLsizei& caps::max_projection_stack_depth()
    {
        return _max_projection_stack_depth;
    }

    const GLsizei& caps::max_projection_stack_depth() const
    {
        return _max_projection_stack_depth;
    }

    GLsizei& caps::max_texture_stack_depth()
    {
        return _max_texture_stack_depth;
    }

    const GLsizei& caps::max_texture_stack_depth() const
    {
        return _max_texture_stack_depth;
    }

    GLsizei& caps::subpixel_bits()
    {
        return _subpixel_bits;
    }

    const GLsizei& caps::subpixel_bits() const
    {
        return _subpixel_bits;
    }

    GLsizei& caps::max_texture_size()
    {
        return _max_texture_size;
    }

    const GLsizei& caps::max_texture_size() const
    {
        return _max_texture_size;
    }

    GLsizei& caps::max_viewport_width()
    {
        return _max_viewport_width;
    }

    const GLsizei& caps::max_viewport_width() const
    {
        return _max_viewport_width;
    }

    GLsizei& caps::max_viewport_height()
    {
        return _max_viewport_height;
    }

    const GLsizei& caps::max_viewport_height() const
    {
        return _max_viewport_height;
    }

    range& caps::aliased_point_size_range()
    {
        return _aliased_point_size_range;
    }

    const range& caps::aliased_point_size_range() const
    {
        return _aliased_point_size_range;
    }

    range& caps::smooth_point_size_range()
    {
        return _smooth_point_size_range;
    }

    const range& caps::smooth_point_size_range() const
    {
        return _smooth_point_size_range;
    }

    range& caps::aliased_line_width_range()
    {
        return _aliased_line_width_range;
    }

    const range& caps::aliased_line_width_range() const
    {
        return _aliased_line_width_range;
    }

    range& caps::smooth_line_width_range()
    {
        return _smooth_line_width_range;
    }

    const range& caps::smooth_line_width_range() const
    {
        return _smooth_line_width_range;
    }

    GLsizei& caps::max_texture_units()
    {
        return _max_texture_units;
    }

    const GLsizei& caps::max_texture_units() const
    {
        return _max_texture_units;
    }

    GLsizei& caps::sample_buffers()
    {
        return _sample_buffers;
    }

    const GLsizei& caps::sample_buffers() const
    {
        return _sample_buffers;
    }

    GLsizei& caps::samples()
    {
        return _samples;
    }

    const GLsizei& caps::samples() const
    {
        return _samples;
    }

    void caps::insert_compressed_format(GLenum format)
    {
        if (std::find(begin(_compressed_texture_formats), end(_compressed_texture_formats), format) == end(_compressed_texture_formats))
        {
            _compressed_texture_formats.push_back(format);
        }
    }

    const GLenum& caps::compressed_format(size_t n) const
    {
        return _compressed_texture_formats[n];
    }

    size_t caps::compressed_format_count() const
    {
        return _compressed_texture_formats.size();
    }

    GLsizei& caps::red_bits()
    {
        return _red_bits;
    }

    const GLsizei& caps::red_bits() const
    {
        return _red_bits;
    }

    GLsizei& caps::green_bits()
    {
        return _green_bits;
    }

    const GLsizei& caps::green_bits() const
    {
        return _green_bits;
    }

    GLsizei& caps::blue_bits()
    {
        return _blue_bits;
    }

    const GLsizei& caps::blue_bits() const
    {
        return _blue_bits;
    }

    GLsizei& caps::alpha_bits()
    {
        return _alpha_bits;
    }

    const GLsizei& caps::alpha_bits() const
    {
        return _alpha_bits;
    }

    GLsizei& caps::depth_bits()
    {
        return _depth_bits;
    }

    const GLsizei& caps::depth_bits() const
    {
        return _depth_bits;
    }

    GLsizei& caps::stencil_bits()
    {
        return _stencil_bits;
    }

    const GLsizei& caps::stencil_bits() const
    {
        return _stencil_bits;
    }

    GLboolean& caps::supports_framebuffer_objects()
    {
        return _supports_framebuffer_objects;
    }

    const GLboolean& caps::supports_framebuffer_objects() const
    {
        return _supports_framebuffer_objects;
    }

    GLsizei& caps::max_renderbuffer_size()
    {
        return _max_renderbuffer_size;
    }

    const GLsizei& caps::max_renderbuffer_size() const
    {
        return _max_renderbuffer_size;
    }

    const GLboolean& caps::supports_rgb8_rgba8() const
    {
        return _supports_rgb8_rgba8;
    }

    GLboolean& caps::supports_rgb8_rgba8()
    {
        return _supports_rgb8_rgba8;
    }

    const GLboolean& caps::supports_depth24() const
    {
        return _supports_depth24;
    }

    GLboolean& caps::supports_depth24()
    {
        return _supports_depth24;
    }

    const GLboolean& caps::supports_depth32() const
    {
        return _supports_depth32;
    }

    GLboolean& caps::supports_depth32()
    {
        return _supports_depth32;
    }

    const GLboolean& caps::supports_stencil1() const
    {
        return _supports_stencil1;
    }

    GLboolean& caps::supports_stencil1()
    {
        return _supports_stencil1;
    }

    const GLboolean& caps::supports_stencil4() const
    {
        return _supports_stencil4;
    }

    GLboolean& caps::supports_stencil4()
    {
        return _supports_stencil4;
    }

    const GLboolean& caps::supports_stencil8() const
    {
        return _supports_stencil8;
    }

    GLboolean& caps::supports_stencil8()
    {
        return _supports_stencil8;
    }

    GLboolean& caps::supports_vertex_array_objects()
    {
        return _supports_vertex_array_objects;
    }

    const GLboolean& caps::supports_vertex_array_objects() const
    {
        return _supports_vertex_array_objects;
    }
}
