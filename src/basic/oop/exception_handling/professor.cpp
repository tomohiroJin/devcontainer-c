#include "professor.h"
#include <sstream>

ProfessorEH::ProfessorEH(const std::string &name, int age) : Person(name, age)
{
  if (age < 0)
  {
    throw std::invalid_argument("Age cannot be negative");
  }
}

std::string ProfessorEH::introduce() const
{
  return "Hello, I am Professor " + getName() + " and I am " + std::to_string(getAge()) + " years old.";
}

void ProfessorEH::setAge(int newAge)
{
  if (newAge < 0)
  {
    throw std::invalid_argument("Age cannot be negative");
  }
  Person::setAge(newAge);
}

void ProfessorEH::setAge(const std::string &newAgeStr)
{
  std::stringstream ss(newAgeStr);
  int newAge;
  ss >> newAge;
  if (ss.fail() || newAge < 0)
  {
    throw std::invalid_argument("Invalid age format or negative age");
  }
  setAge(newAge);
}