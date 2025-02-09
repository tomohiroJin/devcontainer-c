#ifndef PROFESSOR_H
#define PROFESSOR_H

#include "faculty.h"
#include "researcher.h"

// Professor クラス (教員かつ研究者)
class Professor : public Faculty, public Researcher
{
public:
  Professor(const std::string &name, int age);
  std::string introduce() const override;
};

#endif // PROFESSOR_H
