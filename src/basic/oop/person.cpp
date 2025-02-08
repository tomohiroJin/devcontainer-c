// src/basic/oop/person.cpp
#include "person.h"

// Person クラスの実装
Person::Person(const std::string &name, int age) : name(name), age(age) {}
Person::~Person() {}

std::string Person::getName() const { return name; }
int Person::getAge() const { return age; }

void Person::setName(const std::string &newName) { name = newName; }
void Person::setAge(int newAge) { age = newAge; }

std::string Person::introduce() const
{
  return "Hello, my name is " + name + " and I am " + std::to_string(age) + " years old.";
}

// Student クラスの実装
Student::Student(const std::string &name, int age, const std::string &school)
    : Person(name, age), school(school) {}

std::string Student::getSchool() const { return school; }
void Student::setSchool(const std::string &newSchool) { school = newSchool; }

std::string Student::introduce() const
{
  return "Hello, my name is " + getName() + ", I am " + std::to_string(getAge()) + " years old, and I study at " + school + ".";
}
