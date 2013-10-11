#include "fixie_lib/desktop_gl_impl/shader_info.hpp"

#include "fixie_lib/util.hpp"

namespace fixie
{
    namespace desktop_gl_impl
    {
        shader_info::shader_info()
        {
        }

        shader_info::shader_info(const state& state, const caps& caps)
            : _uses_vertex_position(state.vertex_attribute().enabled())
            , _uses_vertex_normal(state.normal_attribute().enabled())
            , _uses_vertex_color(state.color_attribute().enabled())
            , _uses_texture_units(caps.max_texture_units())
            , _uses_clip_planes(caps.max_clip_planes())
            , _uses_lights(caps.max_lights())
            , _shade_model(state.shade_model())
        {
            for (size_t i = 0; i < _uses_texture_units.size(); ++i)
            {
                _uses_texture_units[i] = state.texcoord_attribute(i).enabled();
            }
            for (size_t i = 0; i < _uses_clip_planes.size(); ++i)
            {
                _uses_clip_planes[i] = false; // TODO: create clip plane class with enabled member
            }
            for (size_t i = 0; i < _uses_lights.size(); ++i)
            {
                _uses_lights[i] = state.lights(i).enabled();
            }
        }

        GLboolean shader_info::uses_vertex_position() const
        {
            return _uses_vertex_position;
        }

        GLboolean shader_info::uses_vertex_normal() const
        {
            return _uses_vertex_normal;
        }

        GLboolean shader_info::uses_vertex_color() const
        {
            return _uses_vertex_color;
        }

        GLboolean shader_info::uses_texture_unit(size_t n) const
        {
            return _uses_texture_units[n];
        }

        size_t shader_info::texture_unit_count() const
        {
            return _uses_texture_units.size();
        }

        GLboolean shader_info::uses_clip_plane(size_t n) const
        {
            return _uses_clip_planes[n];
        }

        size_t shader_info::clip_plane_count() const
        {
            return _uses_clip_planes.size();
        }

        GLboolean shader_info::uses_light(size_t n) const
        {
            return _uses_lights[n];
        }

        size_t shader_info::light_count() const
        {
            return _uses_lights.size();
        }

        GLenum shader_info::shade_model() const
        {
            return _shade_model;
        }

        bool operator==(const shader_info& a, const shader_info& b)
        {
            if (a.uses_vertex_position() != b.uses_vertex_position() ||
                a.uses_vertex_normal() != b.uses_vertex_normal() ||
                a.uses_vertex_color() != b.uses_vertex_color())
            {
                return false;
            }

            if (a.texture_unit_count() != b.texture_unit_count())
            {
                return false;
            }
            for (size_t i = 0; i < a.texture_unit_count(); ++i)
            {
                if (a.uses_texture_unit(i) != b.uses_texture_unit(i))
                {
                    return false;
                }
            }

            if (a.clip_plane_count() != b.clip_plane_count())
            {
                return false;
            }
            for (size_t i = 0; i < a.clip_plane_count(); ++i)
            {
                if (a.uses_clip_plane(i) != b.uses_clip_plane(i))
                {
                    return false;
                }
            }

            if (a.light_count() != b.light_count())
            {
                return false;
            }
            for (size_t i = 0; i < a.light_count(); ++i)
            {
                if (a.uses_light(i) != b.uses_light(i))
                {
                    return false;
                }
            }

            if (a.shade_model() != b.shade_model())
            {
                return false;
            }

            return true;
        }
    }
}

namespace std
{
    size_t hash<fixie::desktop_gl_impl::shader_info>::operator()(const fixie::desktop_gl_impl::shader_info& key) const
    {
        size_t seed = 0;
        fixie::hash_combine(seed, key.uses_vertex_position());
        fixie::hash_combine(seed, key.uses_vertex_normal());
        fixie::hash_combine(seed, key.uses_vertex_color());
        for (size_t i = 0; i < key.texture_unit_count(); ++i)
        {
            fixie::hash_combine(seed, key.uses_texture_unit(i));
        }

        for (size_t i = 0; i < key.clip_plane_count(); ++i)
        {
            fixie::hash_combine(seed, key.uses_clip_plane(i));
        }

        for (size_t i = 0; i < key.light_count(); ++i)
        {
            fixie::hash_combine(seed, key.uses_light(i));
        }

        fixie::hash_combine(seed, key.shade_model());

        return seed;
    }
}
