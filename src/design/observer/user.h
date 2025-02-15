#ifndef USER_H
#define USER_H

#include "observer.h"
#include <iostream>

// 具体的な観察者（User）クラス
class User : public Observer
{
private:
  std::string name;

public:
  User(const std::string &name);
  void update(const std::string &message) override;
};

#endif // USER_H
