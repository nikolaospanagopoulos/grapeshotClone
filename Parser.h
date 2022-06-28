#pragma once
#include <string>

#include <vector>
class Parser {

private:
  std::string title{};

  std::string mainContent{};

public:
  void removeScripts(std::string &data);
  void removeCss(std::string &data);
  void removeUnwantedData(std::string &allData);
  void getAllWords();
  void removeComments(std::string &data);
  std::string removeHtmlTags(std::string &html);
};
