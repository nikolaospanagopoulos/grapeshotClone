#include "CategoriesDownloader.h"
#include "Database.h"
#include "Downloader.h"
#include "Exception.h"
#include "JsonParser.h"
#include "Parser.h"
#include <curl/curl.h>
#include <iostream>
#include <string>
int main() {

  try {

    Downloader downloader;

    std::string websiteUrl = "https://www.economist.com/ukraine-crisis";
    downloader.requestData(websiteUrl);

    Parser parser;

    parser.removeUnwantedData(downloader.html_page);

    std::string cleanText = parser.getAllWords();
    // put words in set to make them unique
    parser.fillSetWithWords(cleanText);
    //  put words in deque to add and remove

    parser.fillDeque();

    std::vector<std::string> *randomWords = parser.getRandomWords();
    parser.showRandomWords();

    CategoriesDownloader categories;

    std::vector<std::string> responses;
    for (auto &val : *randomWords) {
      std::cout << val << std::endl;
      std::string word = categories.requestData(val);
      responses.push_back(word);
    }
    JsonParser jsonparser{};
    jsonparser.setResponsesVec(responses);

    std::vector<std::string> *themes =
        jsonparser.createSimilarWordsVec(responses);
    Database myDb{};
    // std::string categoryName{"death"};
    // myDb.insertWordsIntoCategory();
    myDb.analyzeResults(*themes);
  } catch (CustomException &err) {

    std::cerr << err.what() << std::endl;
  }

  return 0;
}
