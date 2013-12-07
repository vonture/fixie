#include "fixie_lib/line_state.hpp"

#include "fixie/fixie_gl_es.h"

namespace fixie
{
    line_state::line_state()
        : _line_width()
        , _line_smooth_enabled()
    {
    }

    const GLfloat& line_state::line_width() const
    {
        return _line_width;
    }

    GLfloat& line_state::line_width()
    {
        return _line_width;
    }

    const GLboolean& line_state::line_smooth_enabled() const
    {
        return _line_smooth_enabled;
    }

    GLboolean& line_state::line_smooth_enabled()
    {
        return _line_smooth_enabled;
    }

    line_state get_default_line_state()
    {
        line_state state;
        state.line_width() = 1.0f;
        state.line_smooth_enabled() = GL_FALSE;
        return state;
    }
}
