#include "Downloader.h"
#include "Exception.h"
#include "Parser.h"
#include <curl/curl.h>
#include <iostream>
int main() {

  try {

    Downloader downloader;

    downloader.requestData();

    // std::cout << downloader.html_page << std::endl;

    Parser parser;

    parser.removeUnwantedData(downloader.html_page);

    std::string cleanText = parser.getAllWords();
    std::cout << "CLEAN TEXT" << std::endl;
    std::cout << cleanText << std::endl;

  } catch (CustomException &err) {

    std::cerr << err.what() << std::endl;
  }

  return 0;
}
