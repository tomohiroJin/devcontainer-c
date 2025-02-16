#ifndef FIZZ_BUZZ_H
#define FIZZ_BUZZ_H

#include <string>

// FizzBuzzクラス
class FizzBuzz
{
private:
  // 入力された数値
  const int inputNumber;

public:
  // コンストラクタ
  FizzBuzz(const int inputNumber);

  // FizzBuzzの結果を返すメソッド
  std::string getResult() const;
};

#endif // FIZZ_BUZZ_H