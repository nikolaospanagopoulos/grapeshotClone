#pragma once
#include <curl/curl.h>

#include <iostream>

#include <string>

static std::string answer;

class Downloader {

public:
  std::string websiteUrl;

  std::string html_page{};

  static size_t functionToWriteResponseToString(char *contents, size_t size,
                                                size_t nmemb, void *userData);

  void requestData();
};
