#include "JsonParser.h"
#include "Exception.h"
#include <string>

void JsonParser::setJsonObj(std::string &data) {
  if (data.size() == 0) {
    throw CustomException(const_cast<char *>("json string is empty"));
  }

  jsonObj = json::parse(data);
}

void JsonParser::printJsonData() const {
  auto jsonIterator = jsonObj.begin();
  while (jsonIterator != jsonObj.end()) {
    std::cout << *jsonIterator << std::endl;
  }
  jsonIterator++;
}

std::vector<std::string> JsonParser::createWordVector()

{
  auto data = jsonObj["response"][0]["items"];
  wordVector.reserve(data.size() + 1);
  std::cout << data.size() << "data size" << std::endl;
  for (int i{}; i < data.size(); i++) {
    wordVector.push_back(data[i]["item"]);
  }
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
