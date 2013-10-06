#ifndef _DESKTOP_GL_CONTEXT_HPP_
#define _DESKTOP_GL_CONTEXT_HPP_

#include <unordered_set>

#include "context.hpp"
#include "desktop_gl_functions.hpp"

namespace fixie
{
    namespace desktop_gl_impl
    {
        class context : public fixie::context_impl
        {
        public:
            context();

            virtual const fixie::caps& caps() override;
            virtual const std::string& renderer_desc() override;

            virtual void initialize_state(fixie::state& state) override;

            virtual std::shared_ptr<texture_impl> create_texture() override;
            virtual std::shared_ptr<buffer_impl> create_buffer() override;

            virtual void draw_arrays(const state& state, GLenum mode, GLint first, GLsizei count) override;
            virtual void draw_elements(const state& state, GLenum mode, GLsizei count, GLenum type, GLvoid* indices) override;

            virtual void clear(const state& state, GLbitfield mask) override;

        private:
            fixie::caps _caps;
            gl_functions _functions;

            std::string _renderer_string;

            GLuint _major_version;
            GLuint _minor_version;
            std::unordered_set<std::string> _extensions;

            color _cur_clear_color;
            GLclampf _cur_clear_depth;
            GLint _cur_clear_stencil;
            void sync_clear_state(const state& state);

            GLboolean _cur_scissor_test;
            rectangle _cur_scissor;
            rectangle _cur_viewport;
            void sync_rasterizer_state(const state& state);

            static void initialize_caps(const gl_functions& functions, fixie::caps& caps);
        };
    }
}

#endif // _DESKTOP_GL_CONTEXT_HPP_
