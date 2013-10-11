#include "gtest/gtest.h"

#include "fixie/fixie.h"

namespace fixie
{
    TEST(context_tests, creation_and_destruction)
    {
        fixie_context ctx = fixie_create_context();
        fixie_destroy_context(ctx);
    }
}
