#include "design/template_method/csv_processor.h"
#include "design/template_method/json_processor.h"
#include <gtest/gtest.h>
#include <sstream>

// 標準出力をキャプチャするためのヘルパー関数
std::string captureOutput(std::function<void()> func)
{
  std::stringstream buffer;
  std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());
  func();
  std::cout.rdbuf(old);
  return buffer.str();
}

// CSVProcessor のテスト
TEST(TemplateMethodTest, CSVProcessing)
{
  CSVProcessor csvProcessor;
  std::string output = captureOutput([&]()
                                     { csvProcessor.processData("data.csv"); });

  EXPECT_NE(output.find("Loading CSV file: data.csv"), std::string::npos);
  EXPECT_NE(output.find("Parsing CSV data..."), std::string::npos);
  EXPECT_NE(output.find("Saving parsed CSV data..."), std::string::npos);
}

// JSONProcessor のテスト
TEST(TemplateMethodTest, JSONProcessing)
{
  JSONProcessor jsonProcessor;
  std::string output = captureOutput([&]()
                                     { jsonProcessor.processData("data.json"); });

  EXPECT_NE(output.find("Loading JSON file: data.json"), std::string::npos);
  EXPECT_NE(output.find("Parsing JSON data..."), std::string::npos);
  EXPECT_NE(output.find("Saving parsed JSON data..."), std::string::npos);
}
