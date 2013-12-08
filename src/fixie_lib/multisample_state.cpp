#include "fixie_lib/multisample_state.hpp"

#include "fixie/fixie_gl_es.h"

namespace fixie
{
    multisample_state::multisample_state()
        : _multisample_enabled()
        , _sample_to_alpha_coverage_enabled()
        , _sample_alpha_to_one_enabled()
        , _sample_coverage_enabled()
        , _sample_coverage_value()
        , _sample_coverage_invert()
    {
    }

    const GLboolean& multisample_state::multisample_enabled() const
    {
        return _multisample_enabled;
    }

    GLboolean& multisample_state::multisample_enabled()
    {
        return _multisample_enabled;
    }

    const GLboolean& multisample_state::sample_to_alpha_coverage_enabled() const
    {
        return _sample_to_alpha_coverage_enabled;
    }

    GLboolean& multisample_state::sample_to_alpha_coverage_enabled()
    {
        return _sample_to_alpha_coverage_enabled;
    }

    const GLboolean& multisample_state::sample_alpha_to_one_enabled() const
    {
        return _sample_alpha_to_one_enabled;
    }

    GLboolean& multisample_state::sample_alpha_to_one_enabled()
    {
        return _sample_alpha_to_one_enabled;
    }

    const GLboolean& multisample_state::sample_coverage_enabled() const
    {
        return _sample_coverage_enabled;
    }

    GLboolean& multisample_state::sample_coverage_enabled()
    {
        return _sample_coverage_enabled;
    }

    const GLfloat& multisample_state::sample_coverage_value() const
    {
        return _sample_coverage_value;
    }

    GLfloat& multisample_state::sample_coverage_value()
    {
        return _sample_coverage_value;
    }

    const GLboolean& multisample_state::sample_coverage_invert() const
    {
        return _sample_coverage_invert;
    }

    GLboolean& multisample_state::sample_coverage_invert()
    {
        return _sample_coverage_invert;
    }

    multisample_state default_multisample_state()
    {
        multisample_state state;
        state.multisample_enabled() = GL_TRUE;
        state.sample_to_alpha_coverage_enabled() = GL_FALSE;
        state.sample_alpha_to_one_enabled() = GL_FALSE;
        state.sample_coverage_enabled() = GL_FALSE;
        state.sample_coverage_value() = 1.0f;
        state.sample_coverage_invert() = GL_FALSE;
        return state;
    }
}
