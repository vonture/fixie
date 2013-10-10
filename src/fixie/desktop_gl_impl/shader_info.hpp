#ifndef _DESKTOP_GL_SHADER_INFO_HPP_
#define _DESKTOP_GL_SHADER_INFO_HPP_

#include "fixie/fixie_gl_types.h"
#include "fixie/state.hpp"
#include "fixie/caps.hpp"

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

            GLboolean uses_vertex_position() const;
            GLboolean uses_vertex_normal() const;
            GLboolean uses_vertex_color() const;
            GLboolean uses_texture_unit(size_t n) const;
            size_t texture_unit_count() const;

            GLboolean uses_clip_plane(size_t n) const;
            size_t clip_plane_count() const;

            GLboolean uses_light(size_t n) const;
            size_t light_count() const;

            GLenum shade_model() const;

        private:
            GLboolean _uses_vertex_position;
            GLboolean _uses_vertex_normal;
            GLboolean _uses_vertex_color;
            std::vector<GLboolean> _uses_texture_units;

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
