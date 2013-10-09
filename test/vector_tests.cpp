#include "gtest/gtest.h"

#include <time.h>
#include <cmath>

#include "fixie/vector.hpp"


namespace fixie
{
    static GLfloat epsilon = 0.0001f;

    GLfloat random_float(GLfloat low, GLfloat high)
    {
        return low + (float)rand() / ((float)RAND_MAX / (high-low));
    }

    class vector_tests : public testing::Test
    {
    protected:
        virtual void SetUp()
        {
            srand((unsigned)time(0));
        }
    };

    TEST_F(vector_tests, constructors)
    {
    }

    TEST_F(vector_tests, length)
    {
        for (size_t i = 0; i < 100; ++i)
        {
            const GLfloat min_comp = -10.0f;
            const GLfloat max_comp = 10.0f;
            vector3 vec(random_float(min_comp, max_comp), random_float(min_comp, max_comp), random_float(min_comp, max_comp));

            GLfloat len_squared = vector3::length_squared(vec);
            GLfloat len = vector3::length(vec);

            EXPECT_LT(std::abs((len * len) - len_squared), epsilon);
        }

        vector3 zero(0.0f, 0.0f, 0.0f);
        EXPECT_EQ(vector3::length(zero), 0.0f);
        EXPECT_EQ(vector3::length_squared(zero), 0.0f);

        vector3 one(1.0f, 0.0f, 0.0f);
        EXPECT_LT(std::abs(vector3::length(one) - 1.0f), epsilon);
        EXPECT_LT(std::abs(vector3::length_squared(one) - 1.0f), epsilon);

        vector3 root_three(1.0f, 1.0f, 1.0f);
        EXPECT_LT(std::abs(vector3::length(root_three) - sqrt(3.0f)), epsilon);
        EXPECT_LT(std::abs(vector3::length_squared(root_three) - 3.0f), epsilon);
    }

    TEST_F(vector_tests, normalize)
    {
        for (size_t i = 0; i < 100; ++i)
        {
            const GLfloat min_comp = -10.0f;
            const GLfloat max_comp = 10.0f;
            vector3 vec(random_float(min_comp, max_comp), random_float(min_comp, max_comp), random_float(min_comp, max_comp));

            GLfloat len_squared = vector3::length_squared(vec);
            GLfloat expected_normalized_len = (len_squared == 0.0f) ? 0.0f : 1.0f;

            EXPECT_LT(std::abs(vector3::length(vector3::normalize(vec)) - expected_normalized_len), epsilon);
        }

        vector3 one(1.0f, 1.0f, 1.0f);
        vector3 normalized_one(vector3::normalize(one));
        GLfloat expected_comp_value = 1.0f / sqrt(3.0f);
        EXPECT_LT(std::abs(normalized_one.x - expected_comp_value), epsilon);
        EXPECT_LT(std::abs(normalized_one.y - expected_comp_value), epsilon);
        EXPECT_LT(std::abs(normalized_one.z - expected_comp_value), epsilon);
    }

    TEST_F(vector_tests, dot)
    {
    }

    TEST_F(vector_tests, cross)
    {
    }
}
