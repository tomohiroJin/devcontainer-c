// src/basic/control/control.cpp
#include "control.h"

// 偶数判定
bool isEven(int num)
{
  return num % 2 == 0;
}

// 2つの数の最大値
int max(int a, int b)
{
  return (a > b) ? a : b;
}

// 三項演算子による条件分岐
int conditionalExpression(bool condition, int trueValue, int falseValue)
{
  return condition ? trueValue : falseValue;
}

// for ループを使った合計計算
int sumWithForLoop(const std::vector<int> &numbers)
{
  int sum = 0;
  for (int num : numbers)
  {
    sum += num;
  }
  return sum;
}

// while ループを使った合計計算
int sumWithWhileLoop(const std::vector<int> &numbers)
{
  int sum = 0;
  size_t i = 0;
  while (i < numbers.size())
  {
    sum += numbers[i];
    ++i;
  }
  return sum;
}

// do-while ループを使った合計計算
int sumWithDoWhileLoop(const std::vector<int> &numbers)
{
  if (numbers.empty())
    return 0;
  int sum = 0;
  size_t i = 0;
  do
  {
    sum += numbers[i];
    ++i;
  } while (i < numbers.size());
  return sum;
}