#include "csv_processor.h"

// CSVファイルを読み込む（仮の処理）
void CSVProcessor::loadData(const std::string &filePath)
{
  std::cout << "Loading CSV file: " << filePath << std::endl;
  data = {"Name, Age", "Alice, 30", "Bob, 25"};
}

// CSVデータを解析する
void CSVProcessor::parseData()
{
  std::cout << "Parsing CSV data..." << std::endl;
  for (const auto &line : data)
  {
    std::cout << "Parsed: " << line << std::endl;
  }
}

// CSVデータを保存する
void CSVProcessor::saveData()
{
  std::cout << "Saving parsed CSV data..." << std::endl;
}
