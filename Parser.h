#pragma once
#include <string>

#include <vector>
class Parser {
  static bool bothAreSpaces(char &lhs, char &rhs) {
    return (lhs == rhs && rhs == ' ');
  }

private:
  std::string title{};

  std::string mainContent{};

public:
  std::string seperateWordsOnCapitalLetter(std::string &data);
  void removeScripts(std::string &data);
  void removeCss(std::string &data);
  void removeUnwantedData(std::string &allData);
  std::string getAllWords();
  std::string removeSpecialChars(std::string &data);
  void removeComments(std::string &data);
  std::string removeHtmlTags(std::string &html);
  void removeSpaces(std::string &data);
};
