#ifndef DATA_PROCESSOR_H
#define DATA_PROCESSOR_H

#include <string>
#include <iostream>

// 抽象クラス（テンプレートメソッドを持つ）
class DataProcessor
{
public:
  virtual ~DataProcessor() = default;

  // テンプレートメソッド：データ処理の流れを統一する
  void processData(const std::string &filePath)
  {
    loadData(filePath);
    parseData();
    saveData();
  }

protected:
  // 各処理はサブクラスで実装する
  virtual void loadData(const std::string &filePath) = 0;
  virtual void parseData() = 0;
  virtual void saveData() = 0;
};

#endif // DATA_PROCESSOR_H
