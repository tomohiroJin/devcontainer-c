#ifndef RAW_POINTER_H
#define RAW_POINTER_H

#include <iostream>

// ポインタの基本操作をまとめた関数群
namespace RawPointer
{
  // 整数のポインタを作成し、値を設定して返す関数
  int *createInt(int value);

  // ポインタを受け取り、値を変更する関数
  void modifyInt(int *p, int newValue);

  // 配列のポインタを作成し、初期化する関数
  int *createArray(int size);

  // 配列のポインタを受け取り、削除する関数
  void deleteArray(int *p);
}

#endif // RAW_POINTER_H