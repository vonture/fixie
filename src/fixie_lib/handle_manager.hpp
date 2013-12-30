#ifndef _HANDLE_MANAGER_HPP_
#define _HANDLE_MANAGER_HPP_

#include <vector>
#include <unordered_map>
#include <memory>

namespace fixie
{
    template <typename handle_type, typename object_type>
    class handle_manager
    {
    public:
        handle_manager(handle_type first_handle = handle_type());

        handle_type allocate_object(std::unique_ptr<object_type> object, bool protected_object = false);
        void insert_object(handle_type handle, std::unique_ptr<object_type> object, bool protected_object = false);
        void erase_object(handle_type handle);

        bool contains_handle(handle_type handle) const;
        bool contains_object(std::weak_ptr<const object_type> object) const;

        handle_type get_handle(std::weak_ptr<const object_type> object) const;
        std::weak_ptr<const object_type> get_object(handle_type handle) const;
        std::weak_ptr<object_type> get_object(handle_type handle);

    private:
        std::unordered_map<handle_type, std::pair<std::shared_ptr<object_type>, bool> > _allocations;

        handle_type _cur_handle;
        std::vector<handle_type> _free_list;
    };
}

#include "handle_manager.inl"

#endif // _HANDLE_MANAGER_HPP_
