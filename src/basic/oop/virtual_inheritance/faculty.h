#ifndef FACULTY_H
#define FACULTY_H

#include "basic/oop/person.h"

// Faculty クラス (教職員)
class Faculty : virtual public Person
{
public:
  Faculty(const std::string &name, int age);
  std::string getRole() const;
};

#endif // FACULTY_H