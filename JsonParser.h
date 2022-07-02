#pragma once
#include "json.h"
#include <vector>

using json = nlohmann::json;

class JsonParser {

public:
  json setJsonObj(std::string &data);
  void printJsonData(json &jsonObj) const;

  std::vector<std::string> similarWordsVec;
  std::vector<std::string> *responsesVec;
  std::vector<std::string> wordVector;
  std::vector<std::string> createWordVector(json &jsonObj);
  void printWordVector() const;
  void setResponsesVec(std::vector<std::string> &responses);
  void printAllResponses() const;
  std::vector<std::string> *
  createSimilarWordsVec(std::vector<std::string> &responses);

private:
};
