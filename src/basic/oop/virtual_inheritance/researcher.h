#ifndef RESEARCHER_H
#define RESEARCHER_H

#include "basic/oop/person.h"

// Researcher クラス (研究者)
class Researcher : virtual public Person
{
public:
  Researcher(const std::string &name, int age);
  std::string doResearch() const;
};

#endif // RESEARCHER_H
