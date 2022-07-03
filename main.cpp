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

    downloader.requestData();

    Parser parser;

    parser.removeUnwantedData(downloader.html_page);

    std::string cleanText = parser.getAllWords();
    // put words in set to make them unique
    parser.fillSetWithWords(cleanText);
    //  put words in deque to add and remove

    parser.fillDeque();
    // parser.readDeque();

    std::vector<std::string> *randomWords = parser.getRandomWords();
    // parser.showRandomWords();

    CategoriesDownloader categories;

    std::vector<std::string> responses;
    Database myDb{};
    myDb.showAllInTable("categories");
    std::string categoryName{"death"};
    // myDb.createAcategory(categoryName);
    myDb.insertWordsIntoCategory();
  } catch (CustomException &err) {

    std::cerr << err.what() << std::endl;
  }

  return 0;
}
