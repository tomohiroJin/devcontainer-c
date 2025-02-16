#include "basic/oop/virtual_inheritance/professor.h"
#include <gtest/gtest.h>

// Professor クラスのテスト
// introduce() の動作確認
// Faculty と Researcher の両方の役割が正しく含まれていることを確認する
TEST(ProfessorTest, TestIntroduce)
{
  Professor p("Dr. Smith", 50);
  EXPECT_EQ(p.introduce(), "Hello, I am Professor Dr. Smith. I am a faculty member. I am conducting research.");
}
