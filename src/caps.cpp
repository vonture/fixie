#include "caps.hpp"

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
}
