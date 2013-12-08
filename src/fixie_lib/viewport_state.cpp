#include "fixie_lib/viewport_state.hpp"

namespace fixie
{
    viewport_state::viewport_state()
        : _viewport()
        , _depth_range()
    {
    }

    rectangle& viewport_state::viewport()
    {
        return _viewport;
    }

    const rectangle& viewport_state::viewport() const
    {
        return _viewport;
    }

    const range& viewport_state::depth_range() const
    {
        return _depth_range;
    }

    range& viewport_state::depth_range()
    {
        return _depth_range;
    }

    viewport_state default_viewport_state()
    {
        viewport_state state;
        state.viewport() = rectangle(0, 0, 1, 1);
        state.depth_range() = range(0.0f, 1.0f);
        return state;
    }
}
