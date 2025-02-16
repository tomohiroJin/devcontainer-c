#include "researcher.h"

Researcher::Researcher(const std::string &name, int age) : Person(name, age) {}
std::string Researcher::doResearch() const
{
  return "I am conducting research.";
}