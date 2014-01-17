namespace fixie
{
    template <typename return_type>
    return_type handle_entry_point_exception(const return_type& return_value)
    {
        handle_entry_point_exception();
        return return_value;
    }
}
