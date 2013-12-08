#include "fixie_lib/pixel_store_state.hpp"

namespace fixie
{
    pixel_store_state::pixel_store_state()
        : _unpack_alignment()
        , _pack_alignment()
    {
    }

    const GLint& pixel_store_state::unpack_alignment() const
    {
        return _unpack_alignment;
    }

    GLint& pixel_store_state::unpack_alignment()
    {
        return _unpack_alignment;
    }

    const GLint& pixel_store_state::pack_alignment() const
    {
        return _pack_alignment;
    }

    GLint& pixel_store_state::pack_alignment()
    {
        return _pack_alignment;
    }

    pixel_store_state default_pixel_store_state()
    {
        pixel_store_state state;
        state.unpack_alignment() = 4;
        state.pack_alignment() = 4;
        return state;
    }
}
