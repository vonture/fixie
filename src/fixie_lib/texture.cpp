#include "fixie_lib/texture.hpp"

#include "fixie/fixie_gl_es.h"

#include <assert.h>

#include "fixie_lib/math_util.hpp"

namespace fixie
{
    texture::texture(std::unique_ptr<texture_impl> impl)
        : _wrap_s(GL_REPEAT)
        , _wrap_t(GL_REPEAT)
        , _min_filter(GL_NEAREST_MIPMAP_LINEAR)
        , _mag_filter(GL_LINEAR)
        , _auto_generate_mipmap(GL_FALSE)
        , _impl(std::move(impl))
    {
    }

    texture::mip_info::mip_info()
        : internal_format(0)
        , width(0)
        , height(0)
    {
    }

    GLenum& texture::wrap_t()
    {
        return _wrap_t;
    }

    const GLenum& texture::wrap_t() const
    {
        return _wrap_t;
    }

    GLenum& texture::wrap_s()
    {
        return _wrap_s;
    }

    const GLenum& texture::wrap_s() const
    {
        return _wrap_s;
    }

    GLenum& texture::min_filter()
    {
        return _min_filter;
    }

    const GLenum& texture::min_filter() const
    {
        return _min_filter;
    }

    GLenum& texture::mag_filter()
    {
        return _mag_filter;
    }

    const GLenum& texture::mag_filter() const
    {
        return _mag_filter;
    }

    GLboolean& texture::auto_generate_mipmap()
    {
        return _auto_generate_mipmap;
    }

    const GLboolean& texture::auto_generate_mipmap() const
    {
        return _auto_generate_mipmap;
    }

    size_t texture::mip_levels() const
    {
        return _mips.size();
    }

    GLsizei texture::mip_level_width(size_t mip) const
    {
        return _mips[mip].width;
    }

    GLsizei texture::mip_level_height(size_t mip) const
    {
        return _mips[mip].height;
    }

    GLenum texture::mip_level_internal_format(size_t mip) const
    {
        return _mips[mip].internal_format;
    }

    GLboolean texture::complete() const
    {
        if (_mips.size() == 0)
        {
            return false;
        }

        if (_mips[0].width <= 0 || _mips[0].height <= 0)
        {
            return false;
        }

        if (_min_filter == GL_NEAREST_MIPMAP_LINEAR || _min_filter == GL_NEAREST_MIPMAP_LINEAR ||
            _min_filter == GL_LINEAR_MIPMAP_NEAREST || _min_filter == GL_LINEAR_MIPMAP_LINEAR)
        {
            size_t required_mip_complete_levels = required_mip_levels(_mips[0].width, _mips[0].height);

            if (_mips.size() != required_mip_complete_levels)
            {
                return false;
            }

            for (size_t i = 0; i < required_mip_complete_levels; ++i)
            {
                if (std::max(_mips[0].width  >> i, 1) != _mips[i].width ||
                    std::max(_mips[0].height >> i, 1) != _mips[i].height)
                {
                    return false;
                }
            }
        }

        return true;
    }

    void texture::set_data(GLint level, GLenum internal_format, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels)
    {
        _impl->set_data(level, internal_format, width, height, format, type, pixels);

        if (_mips.size() <= static_cast<size_t>(level))
        {
            _mips.resize(level + 1);
        }
        _mips[level].internal_format = internal_format;
        _mips[level].width = width;
        _mips[level].height = width;

        if (level == 0 && auto_generate_mipmap())
        {
            generate_mipmaps();
        }
    }

    void texture::set_sub_data(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels)
    {
        _impl->set_sub_data(level, xoffset, yoffset, width, height, format, type, pixels);
        if (level == 0 && auto_generate_mipmap())
        {
            generate_mipmaps();
        }
    }

    void texture::set_compressed_data(GLint level, GLenum internal_format, GLsizei width, GLsizei height, GLsizei image_size, const GLvoid *data)
    {
        _impl->set_compressed_data(level, internal_format, width, height, image_size, data);

        if (_mips.size() <= static_cast<size_t>(level))
        {
            _mips.resize(level + 1);
        }
        _mips[level].internal_format = internal_format;
        _mips[level].width = width;
        _mips[level].height = width;
    }

    void texture::set_compressed_sub_data(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height,
                                          GLenum format, GLsizei image_size, const GLvoid *data)
    {
        _impl->set_compressed_sub_data(level, xoffset, yoffset, width, height, format, image_size, data);
    }

    void texture::copy_data(GLint level, GLenum internal_format, GLint x, GLint y, GLsizei width, GLsizei height,
                            std::weak_ptr<const texture> source)
    {
        std::shared_ptr<const texture> source_locked = source.lock();
        std::weak_ptr<const texture_impl> source_impl = source_locked ? source_locked->impl()
                                                                      : std::weak_ptr<const texture_impl>();
        _impl->copy_data(level, internal_format, x, y, width, height, source_impl);

        if (_mips.size() <= static_cast<size_t>(level))
        {
            _mips.resize(level + 1);
        }
        _mips[level].internal_format = internal_format;
        _mips[level].width = width;
        _mips[level].height = width;

        if (level == 0 && auto_generate_mipmap())
        {
            generate_mipmaps();
        }
    }

    void texture::copy_sub_data(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format,
                                GLenum type, std::weak_ptr<const texture> source)
    {
        std::shared_ptr<const texture> source_locked = source.lock();
        std::weak_ptr<const texture_impl> source_impl = source_locked ? source_locked->impl()
                                                                      : std::weak_ptr<const texture_impl>();
        _impl->copy_sub_data(level, xoffset, yoffset, width, height, format, type, source_impl);
        if (level == 0 && auto_generate_mipmap())
        {
            generate_mipmaps();
        }
    }

    void texture::generate_mipmaps()
    {
        _impl->generate_mipmaps();
        _mips.resize(required_mip_levels(mip_level_width(0), mip_level_height(0)));
        for (size_t i = 0; i < _mips.size(); i++)
        {
            _mips[i].internal_format = _mips[0].internal_format;
            _mips[i].width = std::max(mip_level_width(0) >> i, 1);
            _mips[i].height = std::max(mip_level_height(0) >> i, 1);
        }
    }

    std::weak_ptr<texture_impl> texture::impl()
    {
        return _impl;
    }

    std::weak_ptr<const texture_impl> texture::impl() const
    {
        return _impl;
    }

    size_t texture::required_mip_levels(GLsizei width, GLsizei height) const
    {
        return log2(std::max(width, height));
    }
}
