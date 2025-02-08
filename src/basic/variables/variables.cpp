// src/variables.h
#ifndef VARIABLES_H
#define VARIABLES_H

#include <string>

// 各種データ型のサンプル関数を定義
int getInt();
double getDouble();
bool getBool();
std::string getString();

#endif // VARIABLES_H

// src/variables.cpp
#include "variables.h"

// 整数のサンプルを返す
int getInt()
{
  return 42;
}

// 浮動小数点のサンプルを返す
double getDouble()
{
  return 3.14;
}

// 真偽値のサンプルを返す
bool getBool()
{
  return true;
}

// 文字列のサンプルを返す
std::string getString()
{
  return "Hello, World!";
}
