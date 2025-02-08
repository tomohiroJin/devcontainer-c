// tests/basic/control/test_control.cpp
#include "basic/control/control.h"
#include <gtest/gtest.h>

// 偶数判定関数のテスト
TEST(ControlTest, TestIsEven)
{
  EXPECT_TRUE(isEven(2));  // 2は偶数なのでtrue
  EXPECT_FALSE(isEven(3)); // 3は奇数なのでfalse
}

// 最大値を求める関数のテスト
TEST(ControlTest, TestMax)
{
  EXPECT_EQ(max(5, 10), 10);  // 10のほうが大きい
  EXPECT_EQ(max(-3, -1), -1); // -1のほうが大きい
}

// 三項演算子を使用した条件分岐のテスト
TEST(ControlTest, TestConditionalExpression)
{
  EXPECT_EQ(conditionalExpression(true, 42, 0), 42); // trueの場合42を返す
  EXPECT_EQ(conditionalExpression(false, 42, 0), 0); // falseの場合0を返す
}

// for ループを使った合計計算のテスト
TEST(ControlTest, TestSumWithForLoop)
{
  EXPECT_EQ(sumWithForLoop({1, 2, 3, 4}), 10); // 1+2+3+4=10
  EXPECT_EQ(sumWithForLoop({}), 0);            // 空リストの場合0
}

// while ループを使った合計計算のテスト
TEST(ControlTest, TestSumWithWhileLoop)
{
  EXPECT_EQ(sumWithWhileLoop({1, 2, 3, 4}), 10); // 1+2+3+4=10
  EXPECT_EQ(sumWithWhileLoop({}), 0);            // 空リストの場合0
}

// do-while ループを使った合計計算のテスト
TEST(ControlTest, TestSumWithDoWhileLoop)
{
  EXPECT_EQ(sumWithDoWhileLoop({1, 2, 3, 4}), 10); // 1+2+3+4=10
  EXPECT_EQ(sumWithDoWhileLoop({}), 0);            // 空リストの場合0
}
