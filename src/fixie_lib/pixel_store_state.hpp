#ifndef _PIXEL_STORE_STATE_HPP_
#define _PIXEL_STORE_STATE_HPP_

#include "fixie/fixie_gl_types.h"

namespace fixie
{
    class pixel_store_state
    {
    public:
        pixel_store_state();

        const GLint& unpack_alignment() const;
        GLint& unpack_alignment();

        const GLint& pack_alignment() const;
        GLint& pack_alignment();

    private:
        GLint _unpack_alignment;
        GLint _pack_alignment;
    };

    pixel_store_state get_default_pixel_store_state();
}

#endif // _PIXEL_STORE_STATE_HPP_
