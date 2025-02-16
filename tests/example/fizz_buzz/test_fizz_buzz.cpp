#include "example/fizz_buzz/fizz_buzz.h"
#include <gtest/gtest.h>

// 1 を文字列 "1" に変換する
TEST(FizzBuzzTest, Convert1ToString)
{
  FizzBuzz fizzBuzz = FizzBuzz(1);
  EXPECT_EQ("1", fizzBuzz.getResult());
}

// 3 の倍数を Fizz に変換する
TEST(FizzBuzzTest, Convert3ToFizz)
{
  FizzBuzz fizzBuzz = FizzBuzz(3);
  EXPECT_EQ("Fizz", fizzBuzz.getResult());
}

// 5 の倍数を Buzz に変換する
TEST(FizzBuzzTest, Convert5ToBuzz)
{
  FizzBuzz fizzBuzz = FizzBuzz(5);
  EXPECT_EQ("Buzz", fizzBuzz.getResult());
}

// 15 の倍数を FizzBuzz に変換する
TEST(FizzBuzzTest, Convert15ToFizzBuzz)
{
  FizzBuzz fizzBuzz = FizzBuzz(15);
  EXPECT_EQ("FizzBuzz", fizzBuzz.getResult());
}