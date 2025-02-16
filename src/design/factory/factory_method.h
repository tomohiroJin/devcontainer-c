#ifndef FACTORY_METHOD_H
#define FACTORY_METHOD_H

#include "product.h"
#include <memory>

// 抽象ファクトリクラス
class AbstractFactory
{
public:
  virtual ~AbstractFactory() = default;
  virtual std::unique_ptr<Product> createProduct() const = 0;
};

// 具体的なファクトリA
class ConcreteFactoryA : public AbstractFactory
{
public:
  std::unique_ptr<Product> createProduct() const override
  {
    return std::make_unique<ConcreteProductA>();
  }
};

// 具体的なファクトリB
class ConcreteFactoryB : public AbstractFactory
{
public:
  std::unique_ptr<Product> createProduct() const override
  {
    return std::make_unique<ConcreteProductB>();
  }
};

#endif // FACTORY_METHOD_H
