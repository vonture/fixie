namespace fixie
{
    template <typename value_type>
    value_type clamp(const value_type& val, const value_type& min, const value_type& max)
    {
        return (val < min) ? min : ((val > max) ? max : val);
    }

    template <typename number_type>
    number_type log_two(const number_type& x)
    {
        number_type r = 0;
        while ((x >> r) > 1)
        {
            r++;
        }
        return r;
    }

    template <typename number_type>
    bool is_power_of_two(const number_type& number)
    {
        return !(number == 0) && !(number & (number - 1));
    }
}
