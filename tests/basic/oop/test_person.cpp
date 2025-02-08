// tests/basic/oop/test_person.cpp
#include "basic/oop/person.h"
#include <gtest/gtest.h>

// Person クラスのテスト
// コンストラクタとゲッターの動作確認
TEST(PersonTest, TestConstructorAndGetter)
{
  Person p("Alice", 25);
  EXPECT_EQ(p.getName(), "Alice"); // 名前が正しく設定されているか
  EXPECT_EQ(p.getAge(), 25);       // 年齢が正しく設定されているか
}

// セッターの動作確認
TEST(PersonTest, TestSetter)
{
  Person p("Bob", 30);
  p.setName("Charlie");
  p.setAge(35);
  EXPECT_EQ(p.getName(), "Charlie"); // 名前が正しく変更されているか
  EXPECT_EQ(p.getAge(), 35);         // 年齢が正しく変更されているか
}

// introduce メソッドの動作確認
TEST(PersonTest, TestIntroduce)
{
  Person p("David", 40);
  EXPECT_EQ(p.introduce(), "Hello, my name is David and I am 40 years old.");
}

// Student クラスのテスト
// コンストラクタとゲッターの動作確認
TEST(StudentTest, TestConstructorAndGetter)
{
  Student s("Eve", 20, "XYZ University");
  EXPECT_EQ(s.getName(), "Eve");              // 名前が正しく設定されているか
  EXPECT_EQ(s.getAge(), 20);                  // 年齢が正しく設定されているか
  EXPECT_EQ(s.getSchool(), "XYZ University"); // 学校名が正しく設定されているか
}

// セッターの動作確認
TEST(StudentTest, TestSetter)
{
  Student s("Frank", 22, "ABC College");
  s.setSchool("DEF Institute");
  EXPECT_EQ(s.getSchool(), "DEF Institute"); // 学校名が正しく変更されているか
}

// introduce メソッドの動作確認
TEST(StudentTest, TestIntroduce)
{
  Student s("Grace", 21, "UVW Academy");
  EXPECT_EQ(s.introduce(), "Hello, my name is Grace, I am 21 years old, and I study at UVW Academy.");
}
