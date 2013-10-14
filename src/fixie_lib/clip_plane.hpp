#ifndef _CLIP_PLANE_HPP_
#define _CLIP_PLANE_HPP_

#include "fixie/fixie_gl_types.h"
#include "vector.hpp"

namespace fixie
{
    class clip_plane
    {
    public:
        clip_plane();

        GLboolean& enabled();
        const GLboolean& enabled() const;

        vector4& equation();
        const vector4& equation() const;

    private:
        GLboolean _enabled;
        vector4 _equation;
    };

    clip_plane get_default_clip_plane();
}

#endif // _CLIP_PLANE_HPP_
