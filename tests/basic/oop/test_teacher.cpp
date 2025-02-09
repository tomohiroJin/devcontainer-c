// tests/basic/oop/test_teacher.cpp
#include "basic/oop/teacher.h"
#include <gtest/gtest.h>

// Teacher クラスのテスト
// コンストラクタとゲッターの動作確認
TEST(TeacherTest, TestConstructorAndGetter)
{
  Address addr("Osaka", "456 Elm St");
  Teacher t("Alice", 35, addr, "Mathematics");
  EXPECT_EQ(t.getName(), "Alice");
  EXPECT_EQ(t.getAge(), 35);
  EXPECT_EQ(t.getSubject(), "Mathematics");
  EXPECT_EQ(t.introduce(), "Hello, I am Alice, a teacher of Mathematics, living at 456 Elm St, Osaka.");
}

// work() メソッドの動作確認
TEST(TeacherTest, TestWork)
{
  Address addr("Kyoto", "101 Maple St");
  Teacher t("Charlie", 50, addr, "History");
  EXPECT_EQ(t.work(), "I am teaching History.");
}
