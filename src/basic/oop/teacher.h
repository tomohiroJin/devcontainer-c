// src/basic/oop/teacher.h
#ifndef TEACHER_H
#define TEACHER_H

#include "person.h"

// Address クラス（コンポジションの例）
class Address
{
private:
  std::string city;
  std::string street;

public:
  Address(const std::string &city, const std::string &street);
  std::string getFullAddress() const;
};

// Workable インターフェース（純粋仮想関数のみ）
class Workable
{
public:
  virtual ~Workable() = default;
  virtual std::string work() const = 0;
};

// Teacher クラス（Person を継承し、Workable を実装）
class Teacher : public Person, public Workable
{
private:
  std::string subject;
  Address address; // コンポジション
public:
  Teacher(const std::string &name, int age, const Address &address, const std::string &subject);

  std::string getSubject() const;
  void setSubject(const std::string &newSubject);

  std::string introduce() const override;
  std::string work() const override;
};

#endif // TEACHER_H