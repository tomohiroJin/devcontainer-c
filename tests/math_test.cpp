#include <gtest/gtest.h>
#include "../src/math.h"

// テストケース: add 関数
TEST(MathTest, AddFunction)
{
  EXPECT_EQ(add(2, 3), 5);     // 2 + 3 = 5
  EXPECT_EQ(add(-1, 1), 0);    // -1 + 1 = 0
  EXPECT_EQ(add(0, 0), 0);     // 0 + 0 = 0
  EXPECT_EQ(add(-5, -5), -10); // -5 + -5 = -10
}
