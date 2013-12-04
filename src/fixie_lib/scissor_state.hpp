#ifndef _SCISSOR_STATE_HPP_
#define _SCISSOR_STATE_HPP_

#include "fixie/fixie_gl_types.h"

#include "fixie_lib/rectangle.hpp"

namespace fixie
{
    class scissor_state
    {
    public:
        scissor_state();

        GLboolean& enabled();
        const GLboolean& enabled() const;

        rectangle& scissor();
        const rectangle& scissor() const;

    private:
        GLboolean _enabled;
        rectangle _scissor;
    };

    scissor_state get_default_scissor_state();
}

#endif // _SCISSOR_STATE_HPP_
