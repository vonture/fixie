#ifndef _DESKTOP_GL_SHADER_INFO_HPP_
#define _DESKTOP_GL_SHADER_INFO_HPP_

#include "fixie/fixie_gl_types.h"
#include "fixie_lib/state.hpp"
#include "fixie_lib/caps.hpp"

#include <functional>
#include <cstddef>

namespace fixie
{
    namespace desktop_gl_impl
    {
        class shader_info
        {
        public:
            shader_info();
            explicit shader_info(const state& state, const caps& caps);

            size_t texture_unit_count() const;

            GLboolean uses_clip_plane(size_t n) const;
            size_t clip_plane_count() const;

            GLboolean uses_light(size_t n) const;
            size_t light_count() const;

            GLenum shade_model() const;

        private:
            size_t _texture_unit_count;
            std::vector<GLboolean> _uses_clip_planes;
            std::vector<GLboolean> _uses_lights;
            GLenum _shade_model;
        };

        bool operator==(const shader_info& a, const shader_info& b);
    }
}

namespace std
{
    template <>
    struct hash<fixie::desktop_gl_impl::shader_info> : public std::unary_function<fixie::desktop_gl_impl::shader_info, size_t>
    {
        size_t operator()(const fixie::desktop_gl_impl::shader_info& key) const;
    };
}

#endif // _DESKTOP_GL_SHADER_INFO_HPP_
