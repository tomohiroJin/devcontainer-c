// src/basic/oop/person.h
#ifndef PERSON_H
#define PERSON_H

#include <string>

// Person クラスの定義
class Person
{
private:
  std::string name;
  int age;

public:
  // コンストラクタとデストラクタ
  Person(const std::string &name, int age);
  virtual ~Person();

  // Getter
  std::string getName() const;
  int getAge() const;

  // Setter
  void setName(const std::string &newName);
  void setAge(int newAge);

  // 自己紹介メソッド（仮想関数）
  virtual std::string introduce() const;
};

// Student クラス（Person の派生クラス）
class Student : public Person
{
private:
  std::string school;

public:
  // コンストラクタ
  Student(const std::string &name, int age, const std::string &school);

  // Getter
  std::string getSchool() const;

  // Setter
  void setSchool(const std::string &newSchool);

  // 自己紹介メソッド（オーバーライド）
  std::string introduce() const override;
};

#endif // PERSON_H