#include "Parser.h"
#include <iostream>
#include <regex>
std::string Parser::removeUnwantedData(std::string &allData) {
  int firstBody = allData.find("<body>");
  int lastBody = allData.find("</body");

  int firtHead = allData.find("<title>");
  int lastHead = allData.find("</title>");

  std::string resultTitle = allData.substr(firtHead, lastHead - firtHead);

  std::string resultBody = allData.substr(firstBody, lastBody - firstBody);

  mystream << resultBody;

  // remove html tags
  return resultTitle + resultBody;
}

void Parser::getAllWords() {

  std::vector<std::string> mystrVec{};
  std::string line;

  std::string cleanString = mystream.str();
  std::string allGood = removeHtmlTags(cleanString);
  std::cout << allGood << "all good" << std::endl;
}

std::string Parser::removeHtmlTags(std::string &html) {
  std::regex tags("<[^>]*>");
  std::string remove{};
  return std::regex_replace(html, tags, remove);
}
