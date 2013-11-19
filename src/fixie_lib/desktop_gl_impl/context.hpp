#ifndef _DESKTOP_GL_CONTEXT_HPP_
#define _DESKTOP_GL_CONTEXT_HPP_

#include <unordered_set>

#include "fixie_lib/context.hpp"
#include "fixie_lib/desktop_gl_impl/gl_functions.hpp"
#include "fixie_lib/desktop_gl_impl/shader_cache.hpp"

namespace fixie
{
    namespace desktop_gl_impl
    {
        class context : public fixie::context_impl
        {
        public:
            context();
            virtual ~context();

            virtual const fixie::caps& caps() override;
            virtual const std::string& renderer_desc() override;

            virtual void initialize_state(fixie::state& state) override;

            virtual std::unique_ptr<texture_impl> create_texture() override;
            virtual std::unique_ptr<buffer_impl> create_buffer() override;

            virtual void draw_arrays(const state& state, GLenum mode, GLint first, GLsizei count) override;
            virtual void draw_elements(const state& state, GLenum mode, GLsizei count, GLenum type, const GLvoid* indices) override;

            virtual void clear(const state& state, GLbitfield mask) override;

        private:
            fixie::caps _caps;
            std::shared_ptr<const gl_functions> _functions;
            shader_cache _shader_cache;

            std::string _renderer_string;

            GLuint _major_version;
            GLuint _minor_version;
            std::unordered_set<std::string> _extensions;

            depth_stencil_state _cur_depth_stencil_state;
            void sync_depth_stencil_state(const depth_stencil_state& state);

            clear_state _cur_clear_state;
            void sync_clear_state(const clear_state& state);

            rasterizer_state _cur_rasterizer_state;
            void sync_rasterizer_state(const rasterizer_state& state);

            GLuint _vao;
            void sync_vertex_attribute(const state& state, const vertex_attribute& attribute, GLuint location, GLboolean normalized);
            void sync_vertex_attributes(const state& state, std::weak_ptr<const shader> shader);

            void sync_textures(const state& state);

            void sync_draw_state(const state& state);

            static void initialize_caps(std::shared_ptr<const gl_functions> functions, fixie::caps& caps);
        };
    }
}

#endif // _DESKTOP_GL_CONTEXT_HPP_
