#include "fixie_lib/texture_environment.hpp"
#include "fixie_lib/util.hpp"

#include "fixie/fixie_gl_es.h"

namespace fixie
{
    texture_environment::texture_environment()
        : _texture_enabled(GL_FALSE)
        , _mode(0)
        , _color()
        , _combine_rgb(0)
        , _combine_alpha(0)
        , _source0_rgb(0)
        , _source1_rgb(0)
        , _source2_rgb(0)
        , _source0_alpha(0)
        , _source1_alpha(0)
        , _source2_alpha(0)
        , _operand0_rgb(0)
        , _operand1_rgb(0)
        , _operand2_rgb(0)
        , _operand0_alpha(0)
        , _operand1_alpha(0)
        , _operand2_alpha(0)
        , _rgb_scale(0.0f)
        , _alpha_scale(0.0f)
    {
    }

    GLfloat& texture_environment::alpha_scale()
    {
        return _alpha_scale;
    }

    const GLfloat& texture_environment::alpha_scale() const
    {
        return _alpha_scale;
    }

    GLfloat& texture_environment::rgb_scale()
    {
        return _rgb_scale;
    }

    const GLfloat& texture_environment::rgb_scale() const
    {
        return _rgb_scale;
    }

    GLenum& texture_environment::operand2_alpha()
    {
        return _operand2_alpha;
    }

    const GLenum& texture_environment::operand2_alpha() const
    {
        return _operand2_alpha;
    }

    GLenum& texture_environment::operand1_alpha()
    {
        return _operand1_alpha;
    }

    const GLenum& texture_environment::operand1_alpha() const
    {
        return _operand1_alpha;
    }

    GLenum& texture_environment::operand0_alpha()
    {
        return _operand0_alpha;
    }

    const GLenum& texture_environment::operand0_alpha() const
    {
        return _operand0_alpha;
    }

    GLenum& texture_environment::operand2_rgb()
    {
        return _operand2_rgb;
    }

    const GLenum& texture_environment::operand2_rgb() const
    {
        return _operand2_rgb;
    }

    GLenum& texture_environment::operand1_rgb()
    {
        return _operand1_rgb;
    }

    const GLenum& texture_environment::operand1_rgb() const
    {
        return _operand1_rgb;
    }

    GLenum& texture_environment::operand0_rgb()
    {
        return _operand0_rgb;
    }

    const GLenum& texture_environment::operand0_rgb() const
    {
        return _operand0_rgb;
    }

    GLenum& texture_environment::source2_alpha()
    {
        return _source2_alpha;
    }

    const GLenum& texture_environment::source2_alpha() const
    {
        return _source2_alpha;
    }

    GLenum& texture_environment::source1_alpha()
    {
        return _source1_alpha;
    }

    const GLenum& texture_environment::source1_alpha() const
    {
        return _source1_alpha;
    }

    GLenum& texture_environment::source0_alpha()
    {
        return _source0_alpha;
    }

    const GLenum& texture_environment::source0_alpha() const
    {
        return _source0_alpha;
    }

    GLenum& texture_environment::source2_rgb()
    {
        return _source2_rgb;
    }

    const GLenum& texture_environment::source2_rgb() const
    {
        return _source2_rgb;
    }

    GLenum& texture_environment::source1_rgb()
    {
        return _source1_rgb;
    }

    const GLenum& texture_environment::source1_rgb() const
    {
        return _source1_rgb;
    }

    GLenum& texture_environment::source0_rgb()
    {
        return _source0_rgb;
    }

    const GLenum& texture_environment::source0_rgb() const
    {
        return _source0_rgb;
    }

    GLenum& texture_environment::combine_alpha()
    {
        return _combine_alpha;
    }

    const GLenum& texture_environment::combine_alpha() const
    {
        return _combine_alpha;
    }

    GLenum& texture_environment::combine_rgb()
    {
        return _combine_rgb;
    }

    const GLenum& texture_environment::combine_rgb() const
    {
        return _combine_rgb;
    }

    fixie::color& texture_environment::color()
    {
        return _color;
    }

    const fixie::color& texture_environment::color() const
    {
        return _color;
    }

    GLenum& texture_environment::mode()
    {
        return _mode;
    }

    const GLenum& texture_environment::mode() const
    {
        return _mode;
    }

    GLboolean& texture_environment::texture_enabled()
    {
        return _texture_enabled;
    }

    const GLboolean& texture_environment::texture_enabled() const
    {
        return _texture_enabled;
    }

    texture_environment default_texture_environment()
    {
        texture_environment env;

        // Initial values from ES 1.1.12 spec, table 6.15
        env.texture_enabled() = false;
        env.mode() = GL_MODULATE;
        env.color() = color(0.0f, 0.0f, 0.0f, 0.0f);
        env.combine_rgb() = GL_MODULATE;
        env.combine_alpha() = GL_MODULATE;
        env.source0_rgb() = GL_TEXTURE;
        env.source1_rgb() = GL_PREVIOUS;
        env.source2_rgb() = GL_CONSTANT;
        env.source0_alpha() = GL_TEXTURE;
        env.source1_alpha() = GL_PREVIOUS;
        env.source2_alpha() = GL_CONSTANT;
        env.operand0_rgb() = GL_SRC_COLOR;
        env.operand1_rgb() = GL_SRC_COLOR;
        env.operand2_rgb() = GL_SRC_COLOR;
        env.operand0_alpha() = GL_SRC_ALPHA;
        env.operand1_alpha() = GL_SRC_ALPHA;
        env.operand2_alpha() = GL_SRC_ALPHA;
        env.rgb_scale() = 1.0f;
        env.alpha_scale() = 1.0f;

        return env;
    }

    bool operator==(const texture_environment& a, const texture_environment& b)
    {
        return a.texture_enabled() == b.texture_enabled() &&
               a.mode() == b.mode() &&
               a.color() == b.color() &&
               a.combine_rgb() == b.combine_rgb() &&
               a.combine_alpha() == b.combine_alpha() &&
               a.source0_rgb() == b.source0_rgb() &&
               a.source1_rgb() == b.source1_rgb() &&
               a.source2_rgb() == b.source2_rgb() &&
               a.source0_alpha() == b.source0_alpha() &&
               a.source1_alpha() == b.source1_alpha() &&
               a.source2_alpha() == b.source2_alpha() &&
               a.operand0_rgb() == b.operand0_rgb() &&
               a.operand1_rgb() == b.operand1_rgb()  &&
               a.operand2_rgb() == b.operand2_rgb() &&
               a.operand0_alpha() == b.operand0_alpha()  &&
               a.operand1_alpha() == b.operand1_alpha() &&
               a.operand2_alpha() == b.operand2_alpha() &&
               a.rgb_scale() == b.rgb_scale() &&
               a.alpha_scale() == b.alpha_scale();
    }

    bool operator!=(const texture_environment& a, const texture_environment& b)
    {
        return !(a == b);
    }
}

namespace std
{
    size_t hash<fixie::texture_environment>::operator()(const fixie::texture_environment& key) const
    {
        size_t seed = 0;
        fixie::hash_combine(seed, key.texture_enabled());
        fixie::hash_combine(seed, key.mode());
        fixie::hash_combine(seed, key.color());
        fixie::hash_combine(seed, key.combine_rgb());
        fixie::hash_combine(seed, key.combine_alpha());
        fixie::hash_combine(seed, key.source0_rgb());
        fixie::hash_combine(seed, key.source1_rgb());
        fixie::hash_combine(seed, key.source2_rgb());
        fixie::hash_combine(seed, key.source0_alpha());
        fixie::hash_combine(seed, key.source1_alpha());
        fixie::hash_combine(seed, key.source2_alpha());
        fixie::hash_combine(seed, key.operand0_rgb());
        fixie::hash_combine(seed, key.operand1_rgb());
        fixie::hash_combine(seed, key.operand2_rgb());
        fixie::hash_combine(seed, key.operand0_alpha());
        fixie::hash_combine(seed, key.operand1_alpha());
        fixie::hash_combine(seed, key.operand2_alpha());
        fixie::hash_combine(seed, key.rgb_scale());
        fixie::hash_combine(seed, key.alpha_scale());
        return seed;
    }
}
