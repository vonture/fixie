#ifndef _MULTISAMPLE_STATE_HPP
#define _MULTISAMPLE_STATE_HPP

#include "fixie/fixie_gl_types.h"

namespace fixie
{
    class multisample_state
    {
    public:
        multisample_state();

        const GLboolean& multisample_enabled() const;
        GLboolean& multisample_enabled();

        const GLboolean& sample_to_alpha_coverage_enabled() const;
        GLboolean& sample_to_alpha_coverage_enabled();

        const GLboolean& sample_alpha_to_one_enabled() const;
        GLboolean& sample_alpha_to_one_enabled();

        const GLboolean& sample_coverage_enabled() const;
        GLboolean& sample_coverage_enabled();

        const GLfloat& sample_coverage_value() const;
        GLfloat& sample_coverage_value();

        const GLboolean& sample_coverage_invert() const;
        GLboolean& sample_coverage_invert();

    private:
        GLboolean _multisample_enabled;
        GLboolean _sample_to_alpha_coverage_enabled;
        GLboolean _sample_alpha_to_one_enabled;
        GLboolean _sample_coverage_enabled;
        GLfloat _sample_coverage_value;
        GLboolean _sample_coverage_invert;
    };

    multisample_state default_multisample_state();
}

#endif // _MULTISAMPLE_STATE_HPP
