#ifndef PROFESSOR_H
#define PROFESSOR_H

#include "basic/oop/person.h"
#include <stdexcept>
#include <string>

// Professor クラス
class ProfessorEH : public Person
{
public:
  ProfessorEH(const std::string &name, int age);

  // introduce メソッドのオーバーライド
  std::string introduce() const override;

  // setAge のオーバーロード
  void setAge(int newAge);
  void setAge(const std::string &newAgeStr);
};

#endif // PROFESSOR_H