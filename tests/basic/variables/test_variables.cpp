#include "basic/variables/variables.h"
#include <gtest/gtest.h>

// 各関数のテスト
TEST(VariableTest, TestGetInt)
{
  EXPECT_EQ(getInt(), 42);
}

TEST(VariableTest, TestGetDouble)
{
  EXPECT_DOUBLE_EQ(getDouble(), 3.14);
}

TEST(VariableTest, TestGetBool)
{
  EXPECT_TRUE(getBool());
}

TEST(VariableTest, TestGetString)
{
  EXPECT_EQ(getString(), "Hello, World!");
}
