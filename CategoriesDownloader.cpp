
#include "CategoriesDownloader.h"
#include "Exception.h"
size_t CategoriesDownloader::functionToWriteResponseToString(char *contents,
                                                             size_t size,
                                                             size_t nmemb,
                                                             void *userData) {
  size_t newLength = size * nmemb;
  try {
    dataReturned.append((char *)contents, newLength);
    std::cout << "downloading...." << std::endl;
    std::cout << dataReturned << std::endl;
  } catch (std::bad_alloc &e) {
    std::cerr << e.what() << std::endl;

    return -1;
  }
  return newLength;
}

std::string CategoriesDownloader::requestData(std::string &requestString) {
  CURL *curl;
  CURLcode res;

  std::string firstApiPart{
      "https://api.wordassociations.net/associations/v1.0/json/"
      "search?apikey=044e5f39-d712-40ee-982c-5af57d6d3245&text="};
  std::string lookFor{requestString};
  std::string restOfApiUrl{"&lang=en"};
  std::string allApiCall = firstApiPart + lookFor + restOfApiUrl;
  curl = curl_easy_init();

  if (curl && requestString.size() > 0) {
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,
                     &CategoriesDownloader::functionToWriteResponseToString);
    curl_easy_setopt(curl, CURLOPT_URL, allApiCall.c_str());

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, dataReturned.c_str());

    /* Perform the request, res will get the return code */
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
    res = curl_easy_perform(curl);
    /* Check for errors */
    if (res != CURLE_OK)
      throw CustomException(const_cast<char *>(curl_easy_strerror(res)));
  }
  curl_easy_cleanup(curl);
  return dataReturned;
}
