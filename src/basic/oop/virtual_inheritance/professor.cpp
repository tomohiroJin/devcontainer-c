#include "professor.h"

Professor::Professor(const std::string &name, int age)
    : Person(name, age), Faculty(name, age), Researcher(name, age) {}

std::string Professor::introduce() const
{
  return "Hello, I am Professor " + getName() + ". " + getRole() + " " + doResearch();
}
