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
            , _lighting_enabled(state.lighting_state().enabled())
            , _two_sided_lighting(state.lighting_state().light_model().two_sided_lighting())
            , _uses_lights(caps.max_lights())
            , _uses_light_attenuation(caps.max_lights())
            , _uses_spot_lights(caps.max_lights())
            , _shade_model(state.shade_model())
        {
            for_each_n(0U, _texture_environments.size(), [&](size_t i){ _texture_environments[i] = state.texture_environment(i); });
            for_each_n(0U, _uses_clip_planes.size(), [&](size_t i){ _uses_clip_planes[i] = state.clip_plane(i).enabled(); });
            for_each_n(0U, _uses_lights.size(), [&](size_t i){ _uses_lights[i] = state.lighting_state().light(i).enabled(); });
            for_each_n(0U, _uses_light_attenuation.size(), [&](size_t i){ _uses_light_attenuation[i] = state.lighting_state().light(i).position().w() != 0.0f; });
            for_each_n(0U, _uses_spot_lights.size(), [&](size_t i){ _uses_spot_lights[i] = state.lighting_state().light(i).spot_cutoff() != 180.0f; });
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

        GLboolean shader_info::lighting_enabled() const
        {
            return _lighting_enabled;
        }

        GLboolean shader_info::two_sided_lighting() const
        {
            return _two_sided_lighting;
        }

        GLboolean shader_info::uses_light(size_t n) const
        {
            return _uses_lights[n];
        }

        GLboolean shader_info::uses_light_attenuation(size_t n) const
        {
            return _uses_light_attenuation[n];
        }

        GLboolean shader_info::uses_spot_light(size_t n) const
        {
            return _uses_spot_lights[n];
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
            return a.texture_unit_count() == b.texture_unit_count() &&
                   equal_n(0U, a.texture_unit_count(), [&](size_t i){ return a.texture_environment(i) == b.texture_environment(i); }) &&
                   a.clip_plane_count() == b.clip_plane_count() &&
                   equal_n(0U, a.clip_plane_count(), [&](size_t i){ return a.uses_clip_plane(i) == b.uses_clip_plane(i); }) &&
                   a.lighting_enabled() == b.lighting_enabled() &&
                   a.two_sided_lighting() == b.two_sided_lighting() &&
                   a.light_count() == b.light_count() &&
                   equal_n(0U, a.light_count(), [&](size_t i){ return a.uses_light(i) == b.uses_light(i) &&
                                                                      a.uses_light_attenuation(i) == b.uses_light_attenuation(i) &&
                                                                      a.uses_spot_light(i) == b.uses_spot_light(i); }) &&
                   a.shade_model() == b.shade_model();
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
        fixie::for_each_n(0U, key.clip_plane_count(), [&](size_t i){ fixie::hash_combine(seed, key.uses_clip_plane(i)); });
        fixie::hash_combine(seed, key.lighting_enabled());
        fixie::hash_combine(seed, key.two_sided_lighting());
        fixie::for_each_n(0U, key.light_count(), [&](size_t i){ fixie::hash_combine(seed, key.uses_light(i));
                                                                fixie::hash_combine(seed, key.uses_light_attenuation(i));
                                                                fixie::hash_combine(seed, key.uses_spot_light(i)); });
        fixie::hash_combine(seed, key.shade_model());

        return seed;
    }
}
