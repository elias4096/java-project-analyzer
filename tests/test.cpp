#include <gtest/gtest.h>

// Just some temporarily code to check if googletest works.

int add(int a, int b)
{
    return a + b;
}

TEST(MathTest, Basic)
{
    EXPECT_EQ(add(2, 3), 5);
}
