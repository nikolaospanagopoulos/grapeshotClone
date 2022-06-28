#include "Downloader.h"
#include "Exception.h"
size_t Downloader::functionToWriteResponseToString(char *contents, size_t size,
                                                   size_t nmemb,
                                                   void *userData) {
  size_t newLength = size * nmemb;
  try {
    answer.append((char *)contents, newLength);
  } catch (std::bad_alloc &e) {
    std::cerr << e.what() << std::endl;

    return -1;
  }
  return newLength;
}

void Downloader::requestData() {
  CURL *curl;
  CURLcode res;

  std::string s;
  curl = curl_easy_init();

  if (curl) {
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,
                     &Downloader::functionToWriteResponseToString);
    curl_easy_setopt(curl, CURLOPT_URL, "https://www.pronews.gr");

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, answer.c_str());

    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if (res != CURLE_OK)
      throw CustomException(const_cast<char *>(curl_easy_strerror(res)));
  }
  curl_easy_cleanup(curl);
  html_page = answer;
  std::cout << html_page.size() << std::endl;
}
