#ifndef PAYMENT_STRATEGY_H
#define PAYMENT_STRATEGY_H

#include <string>

// 支払い戦略のインターフェース
class PaymentStrategy
{
public:
  virtual ~PaymentStrategy() = default;
  virtual std::string pay(int amount) const = 0;
};

// クレジットカード支払い
class CreditCardPayment : public PaymentStrategy
{
public:
  std::string pay(int amount) const override;
};

// PayPal 支払い
class PayPalPayment : public PaymentStrategy
{
public:
  std::string pay(int amount) const override;
};

#endif // PAYMENT_STRATEGY_H
