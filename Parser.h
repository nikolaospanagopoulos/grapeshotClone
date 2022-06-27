#pragma once
#include <sstream>
#include <string>

#include <vector>
class Parser {

private:
  std::string allData{};
  std::string title{};

  std::stringstream mystream;

public:
  std::string removeUnwantedData(std::string &allData);
  void getAllWords();
  std::string removeHtmlTags(std::string &html);
};
