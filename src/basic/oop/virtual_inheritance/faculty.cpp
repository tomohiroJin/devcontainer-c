#include "faculty.h"

Faculty::Faculty(const std::string &name, int age) : Person(name, age) {}
std::string Faculty::getRole() const
{
  return "I am a faculty member.";
}
