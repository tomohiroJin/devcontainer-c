// src/basic/control/control.h
#ifndef CONTROL_H
#define CONTROL_H

#include <vector>

// 条件分岐
bool isEven(int num);
int max(int a, int b);
int conditionalExpression(bool condition, int trueValue, int falseValue);

// ループ処理
int sumWithForLoop(const std::vector<int> &numbers);
int sumWithWhileLoop(const std::vector<int> &numbers);
int sumWithDoWhileLoop(const std::vector<int> &numbers);

#endif // CONTROL_H