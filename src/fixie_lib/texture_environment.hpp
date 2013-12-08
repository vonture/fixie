#ifndef _TEXTURE_ENVIRONMENT_HPP_
#define _TEXTURE_ENVIRONMENT_HPP_

#include "fixie/fixie_gl_types.h"
#include "fixie_lib/color.hpp"

#include <functional>
#include <cstddef>

namespace fixie
{
    class texture_environment
    {
    public:
        texture_environment();

        const GLboolean& texture_enabled() const;
        GLboolean& texture_enabled();

        const GLenum& mode() const;
        GLenum& mode();

        const fixie::color& color() const;
        fixie::color& color();

        const GLenum& combine_rgb() const;
        GLenum& combine_rgb();

        const GLenum& combine_alpha() const;
        GLenum& combine_alpha();

        const GLenum& source0_rgb() const;
        GLenum& source0_rgb();

        const GLenum& source1_rgb() const;
        GLenum& source1_rgb();

        const GLenum& source2_rgb() const;
        GLenum& source2_rgb();

        const GLenum& source0_alpha() const;
        GLenum& source0_alpha();

        const GLenum& source1_alpha() const;
        GLenum& source1_alpha();

        const GLenum& source2_alpha() const;
        GLenum& source2_alpha();

        const GLenum& operand0_rgb() const;
        GLenum& operand0_rgb();

        const GLenum& operand1_rgb() const;
        GLenum& operand1_rgb();

        const GLenum& operand2_rgb() const;
        GLenum& operand2_rgb();

        const GLenum& operand0_alpha() const;
        GLenum& operand0_alpha();

        const GLenum& operand1_alpha() const;
        GLenum& operand1_alpha();

        const GLenum& operand2_alpha() const;
        GLenum& operand2_alpha();

        const GLfloat& rgb_scale() const;
        GLfloat& rgb_scale();

        const GLfloat& alpha_scale() const;
        GLfloat& alpha_scale();

    private:
        GLboolean _texture_enabled;
        GLenum _mode;
        fixie::color _color;

        GLenum _combine_rgb;
        GLenum _combine_alpha;

        GLenum _source0_rgb;
        GLenum _source1_rgb;
        GLenum _source2_rgb;

        GLenum _source0_alpha;
        GLenum _source1_alpha;
        GLenum _source2_alpha;

        GLenum _operand0_rgb;
        GLenum _operand1_rgb;
        GLenum _operand2_rgb;

        GLenum _operand0_alpha;
        GLenum _operand1_alpha;
        GLenum _operand2_alpha;

        GLfloat _rgb_scale;
        GLfloat _alpha_scale;
    };

    bool operator==(const texture_environment& a, const texture_environment& b);
    bool operator!=(const texture_environment& a, const texture_environment& b);

    texture_environment default_texture_environment();
}

namespace std
{
    template <>
    struct hash<fixie::texture_environment> : public std::unary_function<fixie::texture_environment, size_t>
    {
        size_t operator()(const fixie::texture_environment& key) const;
    };
}

#endif // _TEXTURE_ENVIRONMENT_HPP_
