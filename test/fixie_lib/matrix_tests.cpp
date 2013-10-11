#include "gtest/gtest.h"

#include <cmath>

#include "fixie_lib/matrix.hpp"

namespace fixie
{
    static GLfloat max_matrix_diff(const matrix4& a, const matrix4& b)
    {
        GLfloat max_diff = 0.0f;
        for (size_t row = 0; row < 4; ++row)
        {
            for (size_t col = 0; col < 4; ++col)
            {
                max_diff = std::max(max_diff, std::abs(a(row, col) - b(row, col)));
            }
        }
        return max_diff;
    }

    static GLfloat epsilon = 0.0001f;

    TEST(matrix_tests, identity)
    {
        fixie::matrix4 mat = fixie::matrix4::identity();

        for (size_t row = 0; row < 4; ++row)
        {
            for (size_t col = 0; col < 4; ++col)
            {
                if (row == col)
                {
                    EXPECT_EQ(mat(row, col), 1.0f);
                }
                else
                {
                    EXPECT_EQ(mat(row, col), 0.0f);
                }
            }
        }
    }

    TEST(matrix_tests, constructors)
    {
        fixie::matrix4 default_constructor;
        EXPECT_EQ(default_constructor, fixie::matrix4::identity());

        GLfloat initial_value_array[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, };
        fixie::matrix4 array_constructor(initial_value_array);

        fixie::matrix4 values_constructor( 0,  4,  8, 12,
                                           1,  5,  9, 13,
                                           2,  6, 10, 14,
                                           3,  7, 11, 15);

        fixie::matrix4 copy_constructor(values_constructor);

        for (size_t row = 0; row < 4; ++row)
        {
            for (size_t col = 0; col < 4; ++col)
            {
                GLfloat expected_value = static_cast<GLfloat>(row + col * 4);
                EXPECT_EQ(array_constructor(row, col), expected_value);
                EXPECT_EQ(values_constructor(row, col), expected_value);
                EXPECT_EQ(copy_constructor(row, col), expected_value);
            }
        }
    }

    TEST(matrix_tests, invert)
    {
        matrix4 mat(1.0f,  0.5f,  0.75f, -2.0f,
                    1.2f,  2.5f,  0.75f,  0.1f,
                    0.1f,  3.5f,  0.65f, -1.0f,
                    5.0f,  0.5f,  0.15f, -2.0f);
        matrix4 double_inverted(matrix4::invert(matrix4::invert(mat)));
        EXPECT_LT(max_matrix_diff(mat, double_inverted), epsilon);

        EXPECT_EQ(matrix4::invert(matrix4::identity()), matrix4::identity());
    }

    TEST(matrix_tests, transpose)
    {
        matrix4 mat(1.0f,  0.5f,  0.75f, -2.0f,
                    1.2f,  2.5f,  0.75f,  0.1f,
                    0.1f,  3.5f,  0.65f, -1.0f,
                    5.0f,  0.5f,  0.15f, -2.0f);

        matrix4 single_transposed(matrix4::transpose(mat));

        for (size_t row = 0; row < 4; ++row)
        {
            for (size_t col = 0; col < 4; ++col)
            {
                EXPECT_EQ(mat(row, col), single_transposed(col, row));
            }
        }

        matrix4 double_transposed(matrix4::transpose(matrix4::transpose(mat)));
        EXPECT_LT(max_matrix_diff(mat, double_transposed), epsilon);
    }

    TEST(matrix_tests, transform)
    {
    }

    TEST(matrix_tests, multiply)
    {
    }
}
