// src/basic/oop/teacher.cpp
#include "teacher.h"

// Address クラスの実装
Address::Address(const std::string &city, const std::string &street) : city(city), street(street) {}
std::string Address::getFullAddress() const
{
  return street + ", " + city;
}

// Teacher クラスの実装
Teacher::Teacher(const std::string &name, int age, const Address &address, const std::string &subject)
    : Person(name, age), address(address), subject(subject) {}

std::string Teacher::getSubject() const { return subject; }
void Teacher::setSubject(const std::string &newSubject) { subject = newSubject; }

std::string Teacher::introduce() const
{
  return "Hello, I am " + getName() + ", a teacher of " + subject + ", living at " + address.getFullAddress() + ".";
}

std::string Teacher::work() const
{
  return "I am teaching " + subject + ".";
}