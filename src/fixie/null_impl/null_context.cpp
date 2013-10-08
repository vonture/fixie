#include "fixie/null_impl/null_context.hpp"
#include "fixie/null_impl/null_texture.hpp"
#include "fixie/null_impl/null_buffer.hpp"

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

        std::shared_ptr<texture_impl> context::create_texture()
        {
            return std::make_shared<texture>();
        }

        std::shared_ptr<buffer_impl> context::create_buffer()
        {
            return std::make_shared<buffer>();
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
