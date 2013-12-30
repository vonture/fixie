#include "fixie_lib/resource_manager.hpp"

namespace fixie
{
    resource_manager::resource_manager()
        : _textures(1)
        , _buffers(1)
    {
    }

    const handle_manager<GLuint, texture>& resource_manager::textures() const
    {
        return _textures;
    }

    handle_manager<GLuint, texture>& resource_manager::textures()
    {
        return _textures;
    }

    const handle_manager<GLuint, buffer>& resource_manager::buffers() const
    {
        return _buffers;
    }

    handle_manager<GLuint, buffer>& resource_manager::buffers()
    {
        return _buffers;
    }
}
