#include <iostream>
#include <vector>
#include "gtest/gtest.h"

#include "matrix.hpp"

using namespace ad6;

TEST(ctor, ilist)
{
  Matrix<int> m1 = {2, 4, {1, 2, 3, 4, 5, 6, 7, 8}};

  for (int i = 0; i < 8; ++i)
    EXPECT_EQ(m1[i / 4][i % 4], i + 1);
}

TEST(mult, fst)
{
  Matrix<int> m1 = Matrix<int>::Identity(5);

  EXPECT_EQ(m1 * m1 == m1, true);
}

TEST(mult, inv)
{
  Matrix<int> m1 = {3, 3, {29, 21, 15,
                           3, 30, 29,
                           14, 28, 22}};
  Matrix<int> m2 = {3, 3, {-152, -42, 159,
                           340, 428, -796,
                           -336, -518, 807}};

  EXPECT_EQ(m1 * m2 == -2308 * Matrix<int>::Identity(3), true);
}

int main( int, char *[] )
{
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
