#include "Parser.h"

std::string Parser::removeUnwantedData(std::string &allData) {
  int firstBody = allData.find("<body>");
  int lastBody = allData.find("</body");

  int firtHead = allData.find("<title>");
  int lastHead = allData.find("</title>");

  std::string resultTitle = allData.substr(firtHead, lastHead - firtHead);

  std::string resultBody = allData.substr(firstBody, lastBody - firstBody);

  return resultTitle + resultBody;
}
