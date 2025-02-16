#ifndef PRODUCT_FACTORY_H
#define PRODUCT_FACTORY_H

#include "product.h"
#include <memory>
#include <string>

class ProductFactory
{
public:
  static std::unique_ptr<Product> createProduct(const std::string &type);
};

#endif // PRODUCT_FACTORY_H
