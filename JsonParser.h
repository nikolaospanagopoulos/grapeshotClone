#pragma once
#include "json.h"
#include <vector>

using json = nlohmann::json;

class JsonParser {

  json jsonObj{};

public:
  void setJsonObj(std::string &data);
  void printJsonData() const;

  std::vector<std::string> wordVector;
  std::vector<std::string> createWordVector();
  void printWordVector() const;

private:
};
