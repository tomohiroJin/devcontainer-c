#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>
#include <string>
#include <memory>

// 観察者（Observer）インターフェース
class Observer
{
public:
  virtual ~Observer() = default;
  virtual void update(const std::string &message) = 0;
};

// 被観察者（Subject）クラス
class Subject
{
private:
  std::vector<std::shared_ptr<Observer>> observers;

public:
  void addObserver(std::shared_ptr<Observer> observer);
  void removeObserver(std::shared_ptr<Observer> observer);
  void notifyObservers(const std::string &message);
};

#endif // OBSERVER_H