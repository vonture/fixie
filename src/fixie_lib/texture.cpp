#include "fixie_lib/texture.hpp"
#include "fixie_lib/framebuffer.hpp"
#include "fixie_lib/math_util.hpp"

#include "fixie/fixie_gl_es.h"

#include <assert.h>

namespace fixie
{
    texture::texture(std::unique_ptr<texture_impl> impl)
        : _sampler_state(get_default_sampler_state())
        , _auto_generate_mipmap(GL_FALSE)
        , _immutable(GL_FALSE)
        , _impl(std::move(impl))
    {
    }

    texture::mip_info::mip_info()
        : internal_format(0)
        , width(0)
        , height(0)
        , compressed(0)
    {
    }

    fixie::sampler_state& texture::sampler_state()
    {
        return _sampler_state;
    }

    const fixie::sampler_state& texture::sampler_state() const
    {
        return _sampler_state;
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

    GLboolean texture::mip_level_compressed(size_t mip) const
    {
        return _mips[mip].compressed;
    }

    GLenum texture::mip_level_internal_format(size_t mip) const
    {
        return _mips[mip].internal_format;
    }

    GLboolean texture::immutable() const
    {
        return _immutable;
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

        if (_sampler_state.min_filter() == GL_NEAREST_MIPMAP_LINEAR || _sampler_state.min_filter() == GL_NEAREST_MIPMAP_LINEAR ||
            _sampler_state.min_filter() == GL_LINEAR_MIPMAP_NEAREST || _sampler_state.min_filter() == GL_LINEAR_MIPMAP_LINEAR)
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

    void texture::set_data(const pixel_store_state& store_state, GLint level, GLenum internal_format, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels)
    {
        assert(_immutable == GL_FALSE);

        _impl->set_data(store_state, level, internal_format, width, height, format, type, pixels);

        if (_mips.size() <= static_cast<size_t>(level))
        {
            _mips.resize(level + 1);
        }
        _mips[level].internal_format = internal_format;
        _mips[level].width = width;
        _mips[level].height = width;
        _mips[level].compressed = GL_FALSE;

        if (level == 0 && auto_generate_mipmap())
        {
            generate_mipmaps();
        }
    }

    void texture::set_sub_data(const pixel_store_state& store_state, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels)
    {
        _impl->set_sub_data(store_state, level, xoffset, yoffset, width, height, format, type, pixels);
        if (level == 0 && auto_generate_mipmap())
        {
            generate_mipmaps();
        }
    }

    void texture::set_compressed_data(const pixel_store_state& store_state, GLint level, GLenum internal_format, GLsizei width, GLsizei height, GLsizei image_size, const GLvoid *data)
    {
        assert(_immutable == GL_FALSE);

        _impl->set_compressed_data(store_state, level, internal_format, width, height, image_size, data);

        if (_mips.size() <= static_cast<size_t>(level))
        {
            _mips.resize(level + 1);
        }
        _mips[level].internal_format = internal_format;
        _mips[level].width = width;
        _mips[level].height = width;
        _mips[level].compressed = GL_TRUE;
    }

    void texture::set_compressed_sub_data(const pixel_store_state& store_state, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height,
                                          GLenum format, GLsizei image_size, const GLvoid *data)
    {
        _impl->set_compressed_sub_data(store_state, level, xoffset, yoffset, width, height, format, image_size, data);
    }

    void texture::set_storage(GLsizei levels, GLenum internal_format, GLsizei width, GLsizei height)
    {
        _impl->set_storage(levels, internal_format, width, height);

        _immutable = GL_TRUE;
        _mips.resize(levels);
        for (size_t i = 0; i < _mips.size(); i++)
        {
            _mips[i].internal_format = internal_format;
            _mips[i].width = std::max(width >> i, 1);
            _mips[i].height = std::max(height >> i, 1);
        }
    }

    void texture::copy_data(GLint level, GLenum internal_format, GLint x, GLint y, GLsizei width, GLsizei height,
                            std::weak_ptr<const framebuffer> source)
    {
        assert(_immutable == GL_FALSE);

        std::shared_ptr<const framebuffer> source_locked = source.lock();
        std::weak_ptr<const framebuffer_impl> source_impl = source_locked ? source_locked->impl()
                                                                          : std::weak_ptr<const framebuffer_impl>();
        _impl->copy_data(level, internal_format, x, y, width, height, source_impl);

        if (_mips.size() <= static_cast<size_t>(level))
        {
            _mips.resize(level + 1);
        }
        _mips[level].internal_format = internal_format;
        _mips[level].width = width;
        _mips[level].height = width;
        _mips[level].compressed = GL_FALSE;

        if (level == 0 && auto_generate_mipmap())
        {
            generate_mipmaps();
        }
    }

    void texture::copy_sub_data(GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width,
                                GLsizei height, GLenum format, GLenum type, std::weak_ptr<const framebuffer> source)
    {
        std::shared_ptr<const framebuffer> source_locked = source.lock();
        std::weak_ptr<const framebuffer_impl> source_impl = source_locked ? source_locked->impl()
                                                                          : std::weak_ptr<const framebuffer_impl>();
        _impl->copy_sub_data(level, xoffset, yoffset, x, y, width, height, format, type, source_impl);
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
            _mips[i].internal_format = mip_level_internal_format(0);
            _mips[i].width = std::max(mip_level_width(0) >> i, 1);
            _mips[i].height = std::max(mip_level_height(0) >> i, 1);
            _mips[i].compressed = mip_level_compressed(0);
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
        return log_two(std::max(width, height));
    }
}
