#include "context.hpp"

namespace fixie
{
    context::context()
        : _front_material(get_default_material())
        , _back_material(get_default_material())
    {
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
}
