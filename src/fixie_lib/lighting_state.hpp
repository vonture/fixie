#ifndef _LIGHTING_STATE_HPP_
#define _LIGHTING_STATE_HPP_

#include "fixie/fixie_gl_types.h"
#include "fixie_lib/caps.hpp"
#include "fixie_lib/material.hpp"
#include "fixie_lib/light.hpp"
#include "fixie_lib/light_model.hpp"

#include <vector>

namespace fixie
{
    class lighting_state
    {
    public:
        lighting_state(size_t light_count);

        GLboolean& enabled();
        const GLboolean& enabled() const;

        material& front_material();
        const material& front_material() const;

        material& back_material();
        const material& back_material() const;

        fixie::light_model& light_model();
        const fixie::light_model& light_model() const;

        fixie::light& light(size_t idx);
        const fixie::light& light(size_t idx) const;

    private:
        GLboolean _enabled;

        material _front_material;
        material _back_material;

        fixie::light_model _light_model;

        std::vector<fixie::light> _lights;
    };

    lighting_state get_default_lighting_state(const caps& caps);
}

#endif // _LIGHTING_STATE_HPP_
