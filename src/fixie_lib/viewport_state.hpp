#ifndef _VIEWPORT_STATE_HPP_
#define _VIEWPORT_STATE_HPP_

#include "fixie/fixie_gl_types.h"

#include "fixie_lib/rectangle.hpp"
#include "fixie_lib/range.hpp"

namespace fixie
{
    class viewport_state
    {
    public:
        viewport_state();

        rectangle& viewport();
        const rectangle& viewport() const;

        const range& depth_range() const;
        range& depth_range();

    private:
        rectangle _viewport;
        range _depth_range;
    };

    viewport_state default_viewport_state();
}

#endif // _VIEWPORT_STATE_HPP_
