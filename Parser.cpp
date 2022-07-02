#include "Parser.h"
#include "Exception.h"
#include <iostream>
#include <random>
#include <regex>
#include <sstream>
void Parser::removeUnwantedData(std::string &allData) {
  int firstBody = allData.find("<body");
  int lastBody = allData.find("</body");

  int firtHead = allData.find("<title");
  int lastHead = allData.find("</title>");

  std::string resultTitle = allData.substr(firtHead, lastHead - firtHead);

  std::string resultBody = allData.substr(firstBody, lastBody - firstBody);

  // remove html tags
  mainContent = resultTitle + resultBody;
}

std::string Parser::getAllWords() {
  std::string cleanedString = removeHtmlTags(mainContent);
  // remove script tags
  removeScripts(cleanedString);
  // remove /**/ comments
  removeComments(cleanedString);
  // remove non alphabetic characters
  // remove special chars
  cleanedString = removeSpecialChars(cleanedString);
  // seperate on capital to get words
  std::string seperatedOnCapital = seperateWordsOnCapitalLetter(cleanedString);
  // remove extra spaces
  removeSpaces(seperatedOnCapital);
  return seperatedOnCapital;
}

std::string Parser::removeHtmlTags(std::string &html) {
  std::regex tags("<[^>]*>");
  std::string remove{};
  return std::regex_replace(html, tags, remove);
}

std::string Parser::removeSpecialChars(std::string &data) {
  const std::regex pattern("[^A-Za-z ]");

  // Replace every matched pattern with the
  // target string using regex_replace() method
  return regex_replace(data, pattern, "");
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
std::string Parser::seperateWordsOnCapitalLetter(std::string &data) {
  std::string newString{};
  for (size_t i{}; i < data.size(); i++) {
    if (std::isupper(data[i]) && i != 0 && data[i - 1] != ' ' &&
        std::islower(data[i - 1])) {
      newString += " ";
    }
    newString += data[i];
  }
  return newString;
}

void Parser::removeSpaces(std::string &data) {
  // put unique chars at the beggining
  std::string::iterator newEnd =
      std::unique(data.begin(), data.end(), bothAreSpaces);
  if (newEnd != data.end()) {
    data.erase(newEnd, data.end());
  }
}

void Parser::fillSetWithWords(std::string &text) {
  std::stringstream wordStream{text};
  std::string temp{};
  while (wordStream >> temp) {
    if (temp.size() > 20 || temp.size() <= 3)
      continue;
    uniqueWords.emplace(temp);
  }
}
void Parser::printSet() const {

  auto setBegin = uniqueWords.begin();

  long int i = 0;
  std::cout << "unique words: " << std::endl;
  while (setBegin != uniqueWords.end()) {

    std::cout << *setBegin << std::endl;
    setBegin++;
    i++;
  }
  std::cout << "the deque has " << i << " words" << std::endl;
}

void Parser::fillDeque() {
  auto setIter = uniqueWords.begin();

  while (setIter != uniqueWords.end()) {
    wordList.push_back(*setIter);
    setIter++;
  }
}

void Parser::readDeque() const {

  auto dequeIter = wordList.begin();

  while (dequeIter != wordList.end()) {
    std::cout << *dequeIter << std::endl;
    dequeIter++;
  }
}

std::vector<std::string> *Parser::getRandomWords() {
  size_t elemenetsToGet{3};

  if (uniqueWords.size() < elemenetsToGet && uniqueWords.size() > 0) {
    elemenetsToGet = uniqueWords.size();

  } else if (uniqueWords.size() == 0) {
    throw new CustomException(
        const_cast<char *>(" set of unique words is empty"));
  }

  std::sample(uniqueWords.begin(), uniqueWords.end(),
              std::back_inserter(randomWordsVec), elemenetsToGet,
              std::mt19937{std::random_device{}()});
  return &randomWordsVec;
}

void Parser::showRandomWords() const {

  std::cout << " RANDOM WORDS: " << std::endl;

  for (auto &word : randomWordsVec) {
    std::cout << word << std::endl;
  }
}
