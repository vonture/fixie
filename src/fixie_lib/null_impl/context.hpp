#ifndef _FIXIE_LIB_NULL_CONTEXT_HPP_
#define _FIXIE_LIB_NULL_CONTEXT_HPP_

#include "fixie_lib/context.hpp"

namespace fixie
{
    namespace null_impl
    {
        class context : public fixie::context_impl
        {
        public:
            virtual const fixie::caps& caps() override;
            virtual const std::string& renderer_desc() override;

            virtual void initialize_state(fixie::state& state) override;

            virtual std::unique_ptr<texture_impl> create_texture() override;
            virtual std::unique_ptr<renderbuffer_impl> create_renderbuffer() override;
            virtual std::unique_ptr<framebuffer_impl> create_default_framebuffer() override;
            virtual std::unique_ptr<framebuffer_impl> create_framebuffer() override;
            virtual std::unique_ptr<buffer_impl> create_buffer() override;

            virtual void draw_arrays(const state& state, GLenum mode, GLint first, GLsizei count) override;
            virtual void draw_elements(const state& state, GLenum mode, GLsizei count, GLenum type, const GLvoid* indices) override;

            virtual void clear(const state& state, GLbitfield mask) override;

            virtual void flush() override;
            virtual void finish() override;
        };
    }
}

#endif // _FIXIE_LIB_NULL_CONTEXT_HPP_
