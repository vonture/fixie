#include "fixie_lib/desktop_gl_impl/shader_info.hpp"

#include <algorithm>

#include "fixie_lib/util.hpp"

namespace fixie
{
    namespace desktop_gl_impl
    {
        shader_info::shader_info()
        {
        }

        shader_info::shader_info(const state& state, const caps& caps)
            : _texture_environments(caps.max_texture_units())
            , _uses_clip_planes(caps.max_clip_planes())
            , _uses_lights(caps.max_lights())
            , _shade_model(state.shade_model())
            , _two_sided_lighting(state.light_model().two_sided_lighting())
        {
            for (size_t i = 0; i < _texture_environments.size(); ++i)
            {
                _texture_environments[i] = state.texture_environment(i);
            }
            for (size_t i = 0; i < _uses_clip_planes.size(); ++i)
            {
                _uses_clip_planes[i] = state.clip_plane(i).enabled();
            }
            for (size_t i = 0; i < _uses_lights.size(); ++i)
            {
                _uses_lights[i] = state.light(i).enabled();
            }
        }

        const fixie::texture_environment& shader_info::texture_environment(size_t n) const
        {
            return _texture_environments[n];
        }

        size_t shader_info::texture_unit_count() const
        {
            return _texture_environments.size();
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

        GLboolean shader_info::two_sided_lighting() const
        {
            return _two_sided_lighting;
        }

        bool operator==(const shader_info& a, const shader_info& b)
        {
            if (a.texture_unit_count() != b.texture_unit_count())
            {
                return false;
            }
            for (size_t i = 0; i < a.texture_unit_count(); ++i)
            {
                if (a.texture_environment(i) != b.texture_environment(i))
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

            if (a.two_sided_lighting() != b.two_sided_lighting())
            {
                return false;
            }

            return true;
        }

        bool operator!=(const shader_info& a, const shader_info& b)
        {
            return !(a == b);
        }
    }
}

namespace std
{
    size_t hash<fixie::desktop_gl_impl::shader_info>::operator()(const fixie::desktop_gl_impl::shader_info& key) const
    {
        size_t seed = 0;

        fixie::hash_combine(seed, key.texture_unit_count());

        for (size_t i = 0; i < key.clip_plane_count(); ++i)
        {
            fixie::hash_combine(seed, key.uses_clip_plane(i));
        }

        for (size_t i = 0; i < key.light_count(); ++i)
        {
            fixie::hash_combine(seed, key.uses_light(i));
        }

        fixie::hash_combine(seed, key.shade_model());
        fixie::hash_combine(seed, key.two_sided_lighting());

        return seed;
    }
}
