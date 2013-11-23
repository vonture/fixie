#include "random.hpp"

#include <cstdlib>
#include <time.h>

namespace sample_util
{
    static bool seed_random()
    {
        srand(time(nullptr));
        return true;
    }

    float random_between(float min_value, float max_value)
    {
        static bool seeded = seed_random();

        float perc = (rand() % 10000) / 10000.0f;
        return min_value + perc * (max_value - min_value);
    }
}
