#include "design/factory/product_factory.h"
#include "design/factory/factory_method.h"
#include <gtest/gtest.h>

// Factory パターンのテスト
TEST(FactoryPatternTest, CreateProductA)
{
  auto product = ProductFactory::createProduct("A");
  ASSERT_NE(product, nullptr);
  EXPECT_EQ(product->getName(), "ConcreteProductA");
}

TEST(FactoryPatternTest, CreateProductB)
{
  auto product = ProductFactory::createProduct("B");
  ASSERT_NE(product, nullptr);
  EXPECT_EQ(product->getName(), "ConcreteProductB");
}

// Factory Method パターンのテスト
TEST(FactoryMethodPatternTest, CreateConcreteProductA)
{
  ConcreteFactoryA factoryA;
  auto product = factoryA.createProduct();
  EXPECT_EQ(product->getName(), "ConcreteProductA");
}

TEST(FactoryMethodPatternTest, CreateConcreteProductB)
{
  ConcreteFactoryB factoryB;
  auto product = factoryB.createProduct();
  EXPECT_EQ(product->getName(), "ConcreteProductB");
}
