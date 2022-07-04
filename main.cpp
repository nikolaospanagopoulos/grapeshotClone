#include "CategoriesDownloader.h"
#include "Database.h"
#include "Downloader.h"
#include "Exception.h"
#include "JsonParser.h"
#include "Parser.h"
#include <curl/curl.h>
#include <iostream>
#include <string>
void doWordRequests(std::vector<std::string> &responses,
                    std::vector<std::string> *randomWords,
                    CategoriesDownloader &categories);
std::vector<std::string> *ParseWebsite(Downloader &downloader, Parser &parser);
int main() {

  try {
    char choice{};

    Database myDb{};
    do {

      std::cout << "1: find what the website is about" << std::endl;
      std::cout << "2: create a new semantic Category" << std::endl;
      std::cout << "3: add words to semantic Category" << std::endl;
      std::cout << "4: show database" << std::endl;
      std::cout << "X: exit" << std::endl;

      std::cin >> choice;
      switch (choice) {
      case '1': {

        Downloader downloader;
        Parser parser;

        std::vector<std::string> *randomWords =
            ParseWebsite(downloader, parser);

        CategoriesDownloader categories;

        std::vector<std::string> responses;

        doWordRequests(responses, randomWords, categories);

        JsonParser jsonparser{};
        jsonparser.setResponsesVec(responses);

        std::vector<std::string> *themes =
            jsonparser.createSimilarWordsVec(responses);
        myDb.analyzeResults(*themes);
        std::cout << std::endl;
        break;
      }
      case '2': {
        std::string categoryName{};
        std::cout << "Please add the name of the category you would like to add"
                  << std::endl;
        std::cin >> categoryName;
        myDb.createAcategory(categoryName);
        std::cout << std::endl;
        std::cout << "thank you" << std::endl;
        break;
      }
      case '3': {
        myDb.insertWordsIntoCategory();
        std::cout << std::endl;
        std::cout << "thank you" << std::endl;
        break;
      }
      case '4': {
        std::string tableName{};
        std::cout << "which database table would you like to see?" << std::endl;

        std::cin >> tableName;
        myDb.showAllInTable(tableName);
        std::cout << std::endl;
        std::cout << "thank you" << std::endl;
        break;
      }
      }
    } while (choice != 'x' && choice != 'X');
  } catch (CustomException &err) {

    std::cerr << err.what() << std::endl;
  }

  return 0;
}

std::vector<std::string> *ParseWebsite(Downloader &downloader, Parser &parser) {

  std::string url{};
  std::cout << "Please type the website url" << std::endl;
  std::cin >> url;
  downloader.requestData(url);

  parser.removeUnwantedData(downloader.html_page);

  std::string cleanText = parser.getAllWords();
  // put words in set to make them unique
  parser.fillSetWithWords(cleanText);
  //  put words in deque to add and remove

  parser.fillDeque();
  //  parser.showRandomWords();
  return parser.getRandomWords();
}

void doWordRequests(std::vector<std::string> &responses,
                    std::vector<std::string> *randomWords,
                    CategoriesDownloader &categories) {

  for (auto &val : *randomWords) {
    std::cout << val << std::endl;
    std::string word = categories.requestData(val);
    responses.push_back(word);
  }
}
