#include "basic/oop/exception_handling/professor.h"
#include <gtest/gtest.h>

// Professor クラスの例外処理のテスト
// 負の年齢を設定すると例外が発生することを確認
TEST(ProfessorEHTest, TestNegativeAgeException)
{
  EXPECT_THROW(ProfessorEH("Dr. Smith", -1), std::invalid_argument);
}

// setAge に負の値を設定した場合の例外処理をテスト
TEST(ProfessorEHTest, TestSetNegativeAgeException)
{
  ProfessorEH p("Dr. Smith", 50);
  EXPECT_THROW(p.setAge(-5), std::invalid_argument);
}

// setAge に無効な文字列を渡した場合の例外処理をテスト
TEST(ProfessorEHTest, TestSetInvalidAgeStringException)
{
  ProfessorEH p("Dr. Smith", 50);
  EXPECT_THROW(p.setAge("invalid"), std::invalid_argument);
}

// ポリモーフィズムのテスト
// Person 型のポインタを使って Professor の introduce() を呼び出し
// 適切にオーバーライドされた introduce() が呼ばれることを確認
TEST(ProfessorEHTest, TestIntroducePolymorphism)
{
  Person *p = new ProfessorEH("Dr. Brown", 45);
  EXPECT_EQ(p->introduce(), "Hello, I am Professor Dr. Brown and I am 45 years old.");
  delete p;
}
