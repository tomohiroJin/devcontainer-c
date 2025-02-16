#ifndef CSV_PROCESSOR_H
#define CSV_PROCESSOR_H

#include "data_processor.h"
#include <vector>

class CSVProcessor : public DataProcessor
{
private:
  std::vector<std::string> data;

protected:
  void loadData(const std::string &filePath) override;
  void parseData() override;
  void saveData() override;
};

#endif // CSV_PROCESSOR_H
