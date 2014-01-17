#ifndef _FIXIE_LIB_RESOURCE_MANAGER_HPP_
#define _FIXIE_LIB_RESOURCE_MANAGER_HPP_

#include "fixie_lib/handle_manager.hpp"
#include "fixie_lib/noncopyable.hpp"
#include "fixie_lib/texture.hpp"
#include "fixie_lib/buffer.hpp"

namespace fixie
{
    class resource_manager : public noncopyable
    {
    public:
        resource_manager();

        const handle_manager<GLuint, texture>& textures() const;
        handle_manager<GLuint, texture>& textures();

        const handle_manager<GLuint, buffer>& buffers() const;
        handle_manager<GLuint, buffer>& buffers();

    private:
        handle_manager<GLuint, texture> _textures;
        handle_manager<GLuint, buffer> _buffers;
    };
}

#endif // _FIXIE_LIB_RESOURCE_MANAGER_HPP_
