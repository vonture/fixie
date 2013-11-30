#include "fixie_lib/lighting_state.hpp"
#include "fixie_lib/util.hpp"

#include "fixie/fixie_gl_es.h"

namespace fixie
{
    lighting_state::lighting_state(size_t light_count)
        : _enabled()
        , _front_material()
        , _back_material()
        , _light_model()
        , _lights(light_count)
    {
    }

    GLboolean& lighting_state::enabled()
    {
        return _enabled;
    }

    const GLboolean& lighting_state::enabled() const
    {
        return _enabled;
    }

    material& lighting_state::front_material()
    {
        return _front_material;
    }

    const material& lighting_state::front_material() const
    {
        return _front_material;
    }

    material& lighting_state::back_material()
    {
        return _back_material;
    }

    const material& lighting_state::back_material() const
    {
        return _back_material;
    }

    fixie::light_model& lighting_state::light_model()
    {
        return _light_model;
    }

    const fixie::light_model& lighting_state::light_model() const
    {
        return _light_model;
    }

    fixie::light& lighting_state::light(size_t idx)
    {
        return _lights[idx];
    }

    const fixie::light& lighting_state::light(size_t idx) const
    {
        return _lights[idx];
    }

    lighting_state get_default_lighting_state(const caps& caps)
    {
        lighting_state state(caps.max_lights());

        state.enabled() = GL_FALSE;
        state.front_material() = get_default_material();
        state.back_material() = get_default_material();
        state.light_model() = get_default_light_model();
        for_each_n(0, caps.max_lights(), [&](size_t i){ state.light(i) = get_default_light(i); });

        return state;
    }
}
