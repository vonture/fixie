#include "fixie_lib/clip_plane.hpp"

#include "fixie/fixie_gl_es.h"

namespace fixie
{
    clip_plane::clip_plane()
        : _enabled(GL_FALSE)
        , _equation(0.0f, 0.0f, 0.0f, 0.0f)
    {
    }

    GLboolean& clip_plane::clip_plane_enabled()
    {
        return _enabled;
    }

    const GLboolean& clip_plane::clip_plane_enabled() const
    {
        return _enabled;
    }

    vector4& clip_plane::equation()
    {
        return _equation;
    }

    const vector4& clip_plane::equation() const
    {
        return _equation;
    }
    
    clip_plane default_clip_plane()
    {
        clip_plane plane;
        plane.clip_plane_enabled() = GL_FALSE;
        plane.equation() = vector4(0.0f, 0.0f, 0.0f, 0.0f);
        return plane;
    }
}
