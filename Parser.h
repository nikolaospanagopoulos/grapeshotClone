#pragma once
#include <deque>
#include <set>
#include <string>
class Parser {
  static bool bothAreSpaces(char &lhs, char &rhs) {
    return (lhs == rhs && rhs == ' ');
  }

private:
  std::string title{};

  std::deque<std::string> wordList{};
  std::set<std::string> uniqueWords{};
  std::string mainContent{};

  void removeComments(std::string &data);
  void removeScripts(std::string &data);
  std::string removeHtmlTags(std::string &html);
  std::string removeSpecialChars(std::string &data);

  void removeSpaces(std::string &data);
  std::string seperateWordsOnCapitalLetter(std::string &data);

public:
  void printSet() const;
  void fillSetWithWords(std::string &text);
  void removeUnwantedData(std::string &allData);
  void fillDeque();
  void readDeque() const;
  std::string getAllWords();
};
