#ifndef _FIXIE_CONTEXT_HPP_
#define _FIXIE_CONTEXT_HPP_

#include "material.hpp"

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

    private:
        material _front_material;
        material _back_material;
    };
}

#endif //_FIXIE_CONTEXT_HPP_
