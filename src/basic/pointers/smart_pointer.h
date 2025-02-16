#ifndef SMART_POINTER_H
#define SMART_POINTER_H

#include <memory>
#include <vector>

namespace SmartPointer
{
  // std::unique_ptr の使用例
  // ヒープ上に確保された整数を保持するスマートポインタ
  // 一つの所有者しか持てず、所有者がなくなるとメモリが自動解放される
  std::unique_ptr<int> createUniqueInt(int value);

  // std::shared_ptr の使用例
  // 参照カウントを持ち、複数の所有者で共有できるスマートポインタ
  // 最後の所有者がなくなるとメモリが解放される
  std::shared_ptr<int> createSharedInt(int value);

  // std::weak_ptr の循環参照回避の例
  // weak_ptr は shared_ptr の所有権を持たず、参照カウントを増やさない
  struct Node
  {
    int value;
    std::shared_ptr<Node> next; // 次のノードを shared_ptr で管理
    std::weak_ptr<Node> prev;   // 前のノードを weak_ptr で管理（循環参照を防ぐため）
    Node(int v) : value(v) {}
  };
}

#endif // SMART_POINTER_H