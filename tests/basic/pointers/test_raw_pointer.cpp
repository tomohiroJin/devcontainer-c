#include "basic/pointers/raw_pointer.h"
#include <gtest/gtest.h>

using namespace RawPointer;

// createInt のテスト
TEST(RawPointerTest, TestCreateInt)
{
  int *p = createInt(10);
  ASSERT_NE(p, nullptr); // ポインタが正しく確保されていることを確認
  EXPECT_EQ(*p, 10);     // 値が正しく設定されていることを確認
  delete p;
}

// modifyInt のテスト
TEST(RawPointerTest, TestModifyInt)
{
  int *p = createInt(5);
  modifyInt(p, 20);
  EXPECT_EQ(*p, 20); // 値が変更されていることを確認
  delete p;
}

// createArray のテスト
TEST(RawPointerTest, TestCreateArray)
{
  int size = 5;
  int *arr = createArray(size);
  ASSERT_NE(arr, nullptr); // 配列が正しく確保されていることを確認
  for (int i = 0; i < size; ++i)
  {
    EXPECT_EQ(arr[i], i + 1); // 配列の初期値が正しく設定されていることを確認
  }
  deleteArray(arr);
}

// deleteArray のテスト
TEST(RawPointerTest, TestDeleteArray)
{
  int *arr = createArray(5);
  deleteArray(arr);
  // 削除後のアクセスは未定義動作なので、アクセスしない
}
