#include "Parser.h"
#include <iostream>
#include <regex>
void Parser::removeUnwantedData(std::string &allData) {
  int firstBody = allData.find("<body");
  int lastBody = allData.find("</body");

  int firtHead = allData.find("<title>");
  int lastHead = allData.find("</title>");

  std::string resultTitle = allData.substr(firtHead, lastHead - firtHead);

  std::string resultBody = allData.substr(firstBody, lastBody - firstBody);

  // remove html tags
  mainContent = resultTitle + resultBody;
}

void Parser::getAllWords() {

  std::vector<std::string> mystrVec{};

  std::string cleanedString = removeHtmlTags(mainContent);
  removeScripts(cleanedString);
  removeComments(cleanedString);
  std::cout << cleanedString << "all good" << std::endl;
}

std::string Parser::removeHtmlTags(std::string &html) {
  std::regex tags("<[^>]*>");
  std::string remove{};
  return std::regex_replace(html, tags, remove);
}

void Parser::removeScripts(std::string &data) {

  std::string::iterator start = data.begin();

  while (start != data.end()) {

    size_t firstScript = data.find("<script");
    size_t lastScript = data.find("</script>");

    if (firstScript != std::string::npos && lastScript != std::string::npos &&
        lastScript > firstScript) {

      std::string commentStr =
          data.substr(firstScript, lastScript - firstScript);
      data.erase(firstScript, commentStr.size());
    }
    start++;
  }
}
void Parser::removeComments(std::string &data) {

  std::string::iterator start = data.begin();

  while (start != data.end()) {

    std::string::size_type firstComment = data.find("/*");
    std::string::size_type lastComment = data.find("*/");

    if (firstComment != std::string::npos && lastComment != std::string::npos &&
        lastComment > firstComment) {
      std::string commentStr =
          data.substr(firstComment, lastComment - firstComment);
      data.erase(firstComment, commentStr.size());
    }
    if (firstComment != std::string::npos && lastComment == std::string::npos) {

      data.erase(firstComment, std::string::npos);
    }
    start++;
  }
}
