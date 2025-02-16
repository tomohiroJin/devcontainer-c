#include "fizz_buzz.h"

FizzBuzz::FizzBuzz(const int inputNumber) : inputNumber(inputNumber) {}

std::string FizzBuzz::getResult() const
{
  if (inputNumber % 15 == 0)
  {
    return "FizzBuzz";
  }
  if (inputNumber % 3 == 0)
  {
    return "Fizz";
  }
  if (inputNumber % 5 == 0)
  {
    return "Buzz";
  }

  return std::to_string(inputNumber);
}