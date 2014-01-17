#ifndef _FIXIE_LIB_LINE_STATE_HPP_
#define _FIXIE_LIB_LINE_STATE_HPP_

#include "fixie/fixie_gl_types.h"

namespace fixie
{
    class line_state
    {
    public:
        line_state();

        const GLfloat& line_width() const;
        GLfloat& line_width();

        const GLboolean& line_smooth_enabled() const;
        GLboolean& line_smooth_enabled();

    private:
        GLfloat _line_width;
        GLboolean _line_smooth_enabled;
    };

    line_state default_line_state();
}

#endif // _FIXIE_LIB_LINE_STATE_HPP_
