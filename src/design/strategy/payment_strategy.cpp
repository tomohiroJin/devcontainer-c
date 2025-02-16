#include "payment_strategy.h"

std::string CreditCardPayment::pay(int amount) const
{
  return "Paid " + std::to_string(amount) + " using Credit Card.";
}

std::string PayPalPayment::pay(int amount) const
{
  return "Paid " + std::to_string(amount) + " using PayPal.";
}
