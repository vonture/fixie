#include "fixie_lib/util.hpp"

namespace fixie
{
    template <typename handle_type, typename object_type>
    handle_manager<handle_type, object_type>::handle_manager(handle_type first_handle)
        : _allocations()
        , _cur_handle(first_handle)
        , _free_list()
    {
    }

    template <typename handle_type, typename object_type>
    handle_type handle_manager<handle_type, object_type>::allocate_object(std::unique_ptr<object_type> object, bool protected_object)
    {
        while (_free_list.size() > 0)
        {
            handle_type handle = _free_list.back();
            _free_list.pop_back();

            if (_allocations.find(handle) == end(_allocations))
            {
                insert_object(handle, std::move(object), protected_object);
                return handle;
            }
        }

        while (_allocations.find(_cur_handle) != end(_allocations))
        {
            ++_cur_handle;
        }

        insert_object(_cur_handle, std::move(object), protected_object);
        return _cur_handle;
    }

    template <typename handle_type, typename object_type>
    void handle_manager<handle_type, object_type>::insert_object(handle_type handle, std::unique_ptr<object_type> object,
                                                                        bool protected_object)
    {
        _allocations.insert(std::make_pair(handle, std::make_pair(std::shared_ptr<object_type>(std::move(object)), protected_object)));
    }

    template <typename handle_type, typename object_type>
    void handle_manager<handle_type, object_type>::erase_object(handle_type handle)
    {
        auto iter = _allocations.find(handle);
        if (iter != _allocations.end() && !iter->second.second)
        {
            _allocations.erase(iter);
            _free_list.push_back(handle);
        }
    }

    template <typename handle_type, typename object_type>
    bool handle_manager<handle_type, object_type>::contains_handle(handle_type handle) const
    {
        return _allocations.find(handle) != end(_allocations);
    }

    namespace priv
    {
        template <typename iterator_type, typename second_type>
        static iterator_type reverse_find_handle(iterator_type first, iterator_type last, const second_type& item)
        {
            for (iterator_type i = first; i != last; ++i)
            {
                if (i->second.first == item)
                {
                    return i;
                }
            }

            return last;
        }
    }

    template <typename handle_type, typename object_type>
    bool handle_manager<handle_type, object_type>::contains_object(std::weak_ptr<const object_type> object) const
    {
        return priv::reverse_find_handle(begin(_allocations), end(_allocations), object.lock()) != end(_allocations);
    }

    template <typename handle_type, typename object_type>
    handle_type handle_manager<handle_type, object_type>::get_handle(std::weak_ptr<const object_type> object) const
    {
        return priv::reverse_find_handle(begin(_allocations), end(_allocations), object.lock())->first;
    }

    template <typename handle_type, typename object_type>
    std::weak_ptr<const object_type> handle_manager<handle_type, object_type>::get_object(handle_type handle) const
    {
        auto iter = _allocations.find(handle);
        return (iter != end(_allocations)) ? iter->second.first : std::weak_ptr<object_type>();
    }

    template <typename handle_type, typename object_type>
    std::weak_ptr<object_type> handle_manager<handle_type, object_type>::get_object(handle_type handle)
    {
        auto iter = _allocations.find(handle);
        return (iter != end(_allocations)) ? iter->second.first : std::weak_ptr<object_type>();
    }
}
