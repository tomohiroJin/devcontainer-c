#ifndef SHOPPING_CART_H
#define SHOPPING_CART_H

#include "payment_strategy.h"
#include <memory>

// ショッピングカートクラス
class ShoppingCart
{
private:
  std::unique_ptr<PaymentStrategy> paymentStrategy;

public:
  void setPaymentStrategy(std::unique_ptr<PaymentStrategy> strategy);
  std::string checkout(int amount) const;
};

#endif // SHOPPING_CART_H