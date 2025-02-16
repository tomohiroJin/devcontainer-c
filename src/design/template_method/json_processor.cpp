#include "json_processor.h"

// JSONファイルを読み込む（仮の処理）
void JSONProcessor::loadData(const std::string &filePath)
{
  std::cout << "Loading JSON file: " << filePath << std::endl;
  data = {"{\"name\": \"Alice\", \"age\": 30}", "{\"name\": \"Bob\", \"age\": 25}"};
}

// JSONデータを解析する
void JSONProcessor::parseData()
{
  std::cout << "Parsing JSON data..." << std::endl;
  for (const auto &line : data)
  {
    std::cout << "Parsed: " << line << std::endl;
  }
}

// JSONデータを保存する
void JSONProcessor::saveData()
{
  std::cout << "Saving parsed JSON data..." << std::endl;
}
