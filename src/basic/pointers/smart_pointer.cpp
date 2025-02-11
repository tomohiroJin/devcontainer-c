#include "smart_pointer.h"

namespace SmartPointer
{
  // std::unique_ptr の作成
  // ヒープ上に整数を確保し、所有権を unique_ptr に持たせる
  std::unique_ptr<int> createUniqueInt(int value)
  {
    return std::make_unique<int>(value);
  }

  // std::shared_ptr の作成
  // shared_ptr により、複数の所有者で整数を共有可能
  std::shared_ptr<int> createSharedInt(int value)
  {
    return std::make_shared<int>(value);
  }
}
