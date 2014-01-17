#ifndef _FIXIE_LIB_SCISSOR_STATE_HPP_
#define _FIXIE_LIB_SCISSOR_STATE_HPP_

#include "fixie/fixie_gl_types.h"

#include "fixie_lib/rectangle.hpp"

namespace fixie
{
    class scissor_state
    {
    public:
        scissor_state();

        GLboolean& scissor_test_enabled();
        const GLboolean& scissor_test_enabled() const;

        rectangle& scissor();
        const rectangle& scissor() const;

    private:
        GLboolean _scissor_test_enabled;
        rectangle _scissor;
    };

    scissor_state default_scissor_state();
}

#endif // _FIXIE_LIB_SCISSOR_STATE_HPP_
