#include "gtest/gtest.h"

#include "fixie_lib/util.hpp"

#include <map>

namespace fixie
{
    TEST(reverse_find, basic_reverse_find)
    {
        typedef std::map<int, int> map_type;
        map_type map;
        map[0] = 1;
        map[1] = 2;
        map[3] = 4;

        EXPECT_EQ(fixie::reverse_find(begin(map), end(map), 1)->first, 0);
        EXPECT_EQ(fixie::reverse_find(begin(map), end(map), 1)->second, 1);

        EXPECT_EQ(fixie::reverse_find(begin(map), end(map), 2)->first, 1);
        EXPECT_EQ(fixie::reverse_find(begin(map), end(map), 4)->first, 3);

        EXPECT_EQ(fixie::reverse_find(begin(map), end(map), 0), end(map));
        EXPECT_EQ(fixie::reverse_find(begin(map), end(map), 5), end(map));
    }
}
