#include "JsonParser.h"
#include "Exception.h"
#include <string>

json JsonParser::setJsonObj(std::string &data) {
  if (data.size() == 0) {
    throw CustomException(const_cast<char *>("json string is empty"));
  }

  return json::parse(data);
}

void JsonParser::printJsonData(json &jsonObj) const {
  auto jsonIterator = jsonObj.begin();
  while (jsonIterator != jsonObj.end()) {
    std::cout << *jsonIterator << std::endl;
  }
  jsonIterator++;
}

std::vector<std::string> JsonParser::createWordVector(json &jsonObj)

{
  auto data = jsonObj["response"][0]["items"];
  std::cout << data.size() << "data size" << std::endl;
  for (size_t i{}; i < data.size(); i++) {
    wordVector.push_back(data[i]["item"]);
  }
  jsonObj.erase(jsonObj.begin(), jsonObj.end());
  return wordVector;
}

void JsonParser::printWordVector() const {

  auto wordIter = wordVector.begin();
  while (wordIter != wordVector.end()) {
    std::cout << "word "
              << ":" << *wordIter << std::endl;
    wordIter++;
  }
}

void JsonParser::setResponsesVec(std::vector<std::string> &responses) {

  responsesVec = &responses;
}

void JsonParser::printAllResponses() const {
  auto iter = responsesVec->begin();
  while (iter != responsesVec->end()) {
    std::cout << *iter << std::endl;
    iter++;
  }
}

std::vector<std::string> *
JsonParser::createSimilarWordsVec(std::vector<std::string> &responses) {

  for (auto &res : responses) {

    json tempJson = setJsonObj(res);
    auto data = tempJson["response"][0]["items"];
    for (size_t i{}; i < data.size(); i++) {
      similarWordsVec.push_back(data[i]["item"]);
    }
  }
  return &similarWordsVec;
}
