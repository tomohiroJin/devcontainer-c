#include "raw_pointer.h"
#include <iostream>

namespace RawPointer
{
  // ヒープ上に整数を作成し、ポインタを返す
  int *createInt(int value)
  {
    int *p = new int(value);
    return p;
  }

  // ポインタを受け取り、値を変更する
  void modifyInt(int *p, int newValue)
  {
    if (p)
    {
      *p = newValue;
    }
  }

  // ヒープ上に配列を作成し、ポインタを返す
  int *createArray(int size)
  {
    if (size <= 0)
      return nullptr;
    int *arr = new int[size];
    for (int i = 0; i < size; ++i)
    {
      arr[i] = i + 1;
    }
    return arr;
  }

  // 配列を削除する
  void deleteArray(int *p)
  {
    delete[] p;
  }
}