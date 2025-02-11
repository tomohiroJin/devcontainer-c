#include "basic/pointers/smart_pointer.h"
#include <gtest/gtest.h>

using namespace SmartPointer;

// std::unique_ptr のテスト
// unique_ptr は単独の所有者しか持てないことを確認
TEST(SmartPointerTest, TestUniquePtr)
{
  std::unique_ptr<int> p = createUniqueInt(42);
  ASSERT_NE(p, nullptr); // ポインタが正しく確保されていることを確認
  EXPECT_EQ(*p, 42);     // 値が正しく設定されていることを確認
                         // unique_ptr のスコープを抜けるとメモリが解放される
}

// std::shared_ptr のテスト
// shared_ptr は複数の所有者で共有され、参照カウントが増減することを確認
TEST(SmartPointerTest, TestSharedPtr)
{
  std::shared_ptr<int> p1 = createSharedInt(100);
  std::shared_ptr<int> p2 = p1; // 共有所有権を持つ
  EXPECT_EQ(*p1, 100);
  EXPECT_EQ(*p2, 100);
  EXPECT_EQ(p1.use_count(), 2); // 参照カウントが 2 になっていることを確認
                                // どちらの shared_ptr もスコープを抜けるとメモリが解放される
}

// std::weak_ptr の循環参照回避テスト
// weak_ptr を使って循環参照が発生しないことを確認
TEST(SmartPointerTest, TestWeakPtr)
{
  std::shared_ptr<Node> node1 = std::make_shared<Node>(1);
  std::shared_ptr<Node> node2 = std::make_shared<Node>(2);
  node1->next = node2;
  node2->prev = node1;                        // weak_ptr なので参照カウントは増えない
  EXPECT_EQ(node1->next->value, 2);           // next の値が正しいことを確認
  EXPECT_TRUE(node2->prev.lock() != nullptr); // weak_ptr から shared_ptr に変換できることを確認
}
