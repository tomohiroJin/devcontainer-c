#include "design/strategy/shopping_cart.h"
#include "design/strategy/payment_strategy.h"
#include <gtest/gtest.h>

// クレジットカード支払いのテスト
TEST(StrategyTest, TestCreditCardPayment)
{
  ShoppingCart cart;
  cart.setPaymentStrategy(std::make_unique<CreditCardPayment>());
  EXPECT_EQ(cart.checkout(100), "Paid 100 using Credit Card.");
}

// PayPal 支払いのテスト
TEST(StrategyTest, TestPayPalPayment)
{
  ShoppingCart cart;
  cart.setPaymentStrategy(std::make_unique<PayPalPayment>());
  EXPECT_EQ(cart.checkout(200), "Paid 200 using PayPal.");
}

// 支払い戦略が未設定の場合のテスト
TEST(StrategyTest, TestNoPaymentStrategy)
{
  ShoppingCart cart;
  EXPECT_EQ(cart.checkout(300), "No payment strategy set.");
}
