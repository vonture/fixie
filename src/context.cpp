#include "context.hpp"

namespace fixie
{
    context::context()
        : _front_material(get_default_material())
        , _back_material(get_default_material())
    {
        for (size_t i = 0; i < _light_count; i++)
        {
            _lights[i] = get_default_light(i);
        }
    }

    material& context::front_material()
    {
        return _front_material;
    }

    const material& context::front_material() const
    {
        return _front_material;
    }

    material& context::back_material()
    {
        return _back_material;
    }

    const material& context::back_material() const
    {
        return _back_material;
    }

    light& context::lights(size_t idx)
    {
        return _lights[idx];
    }

    const light& context::lights(size_t idx) const
    {
        return _lights[idx];
    }

    size_t context::light_count() const
    {
        return _light_count;
    }
}
