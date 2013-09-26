#ifndef _FIXIE_CONTEXT_HPP_
#define _FIXIE_CONTEXT_HPP_

#include "material.hpp"
#include "light.hpp"

namespace fixie
{
    class context
    {
    public:
        context();

        material& front_material();
        const material& front_material() const;

        material& back_material();
        const material& back_material() const;

        light& lights(size_t idx);
        const light& lights(size_t idx) const;
        size_t light_count() const;

    private:
        material _front_material;
        material _back_material;

        static const size_t _light_count = 8;
        light _lights[_light_count];
    };
}

#endif //_FIXIE_CONTEXT_HPP_
