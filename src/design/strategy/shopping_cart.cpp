#include "shopping_cart.h"

void ShoppingCart::setPaymentStrategy(std::unique_ptr<PaymentStrategy> strategy)
{
  paymentStrategy = std::move(strategy);
}

std::string ShoppingCart::checkout(int amount) const
{
  if (paymentStrategy)
  {
    return paymentStrategy->pay(amount);
  }
  return "No payment strategy set.";
}