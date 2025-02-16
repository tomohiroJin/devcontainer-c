#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <memory>

// 抽象クラス Product
class Product
{
public:
  virtual ~Product() = default;
  virtual std::string getName() const = 0;
};

// 具体的な製品A
class ConcreteProductA : public Product
{
public:
  std::string getName() const override
  {
    return "ConcreteProductA";
  }
};

// 具体的な製品B
class ConcreteProductB : public Product
{
public:
  std::string getName() const override
  {
    return "ConcreteProductB";
  }
};

#endif // PRODUCT_H
