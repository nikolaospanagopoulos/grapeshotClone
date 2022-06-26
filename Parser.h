#pragma once
#include <string>

class Parser {

private:
  std::string title{};

public:
  std::string removeUnwantedData(std::string &allData);
};
