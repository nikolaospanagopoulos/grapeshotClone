#pragma once
#include "json.h"
#include <curl/curl.h>
#include <string>
static std::string dataReturned;
class CategoriesDownloader {
public:
  static size_t functionToWriteResponseToString(char *contents, size_t size,
                                                size_t nmemb, void *userData);

  std::string requestData(std::string &requestString);
};
