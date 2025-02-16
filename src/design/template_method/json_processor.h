#ifndef JSON_PROCESSOR_H
#define JSON_PROCESSOR_H

#include "data_processor.h"
#include <vector>

class JSONProcessor : public DataProcessor
{
private:
  std::vector<std::string> data;

protected:
  void loadData(const std::string &filePath) override;
  void parseData() override;
  void saveData() override;
};

#endif // JSON_PROCESSOR_H
