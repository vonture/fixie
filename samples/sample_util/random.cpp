#include "random.hpp"

#include <cstdlib>
#include <time.h>

namespace sample_util
{
    static bool seed_random()
    {
        static bool seeded = false;
        if (!seeded)
        {
            srand(static_cast<unsigned int>(time(nullptr)));
            seeded = true;
        }
        return seeded;
    }

    float random_between(float min_value, float max_value)
    {
        static bool seeded = seed_random();

        float perc = (rand() % 10000) / 10000.0f;
        return min_value + perc * (max_value - min_value);
    }

    bool random_bool()
    {
        static bool seeded = seed_random();
        return rand() % 2 == 0;
    }
}
