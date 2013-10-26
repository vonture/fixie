#include "fixie_lib/null_impl/context.hpp"
#include "fixie_lib/null_impl/texture.hpp"
#include "fixie_lib/null_impl/buffer.hpp"

namespace fixie
{
    namespace null_impl
    {
        const fixie::caps& context::caps()
        {
            static const fixie::caps caps;
            return caps;
        }

        const std::string& context::renderer_desc()
        {
            static const std::string renderer_string("null");
            return renderer_string;
        }

        void context::initialize_state(fixie::state& state)
        {
        }

        std::unique_ptr<texture_impl> context::create_texture()
        {
            return std::unique_ptr<texture_impl>(new texture());
        }

        std::unique_ptr<buffer_impl> context::create_buffer()
        {
            return std::unique_ptr<buffer_impl>(new buffer());
        }

        void context::draw_arrays(const state& state, GLenum mode, GLint first, GLsizei count)
        {
        }

        void context::draw_elements(const state& state, GLenum mode, GLsizei count, GLenum type, const GLvoid* indices)
        {
        }

        void context::clear(const state& state, GLbitfield mask)
        {
        }
    }
}
