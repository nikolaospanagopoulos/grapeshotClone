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

    std::cout << "clean data" << std::endl;
    std::cout << parser.removeUnwantedData(downloader.html_page) << std::endl;

  } catch (CustomException &err) {

    std::cerr << err.what() << std::endl;
  }

  return 0;
}
