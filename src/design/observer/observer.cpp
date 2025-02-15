#include "observer.h"
#include <algorithm> // std::remove_if を使用するために必要

void Subject::addObserver(std::shared_ptr<Observer> observer)
{
  observers.push_back(observer);
}

void Subject::removeObserver(std::shared_ptr<Observer> observer)
{
  auto it = std::remove_if(observers.begin(), observers.end(),
                           [&observer](const std::shared_ptr<Observer> &o)
                           { return o == observer; });

  if (it != observers.end())
  {
    observers.erase(it, observers.end());
  }
}

void Subject::notifyObservers(const std::string &message)
{
  for (const auto &observer : observers)
  {
    observer->update(message);
  }
}
