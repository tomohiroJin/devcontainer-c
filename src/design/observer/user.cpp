#include "user.h"

User::User(const std::string &name) : name(name) {}

void User::update(const std::string &message)
{
  std::cout << "User " << name << " received message: " << message << std::endl;
}