#include "product_factory.h"

std::unique_ptr<Product> ProductFactory::createProduct(const std::string &type)
{
  if (type == "A")
  {
    return std::make_unique<ConcreteProductA>();
  }
  else if (type == "B")
  {
    return std::make_unique<ConcreteProductB>();
  }
  return nullptr;
}
