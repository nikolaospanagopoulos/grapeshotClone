#pragma once
#include "mysql_connection.h"
#include <map>
#include <vector>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

class Database {
  sql::Driver *driver;
  sql::Connection *con;
  sql::Statement *stmt;
  sql::ResultSet *res;
  std::map<std::string, size_t> resultsMap;
  std::vector<std::string> resultsNumVec;

public:
  Database();
  ~Database();
  void showAllInTable(std::string &tableName);
  void createAcategory(std::string &categoryName);
  void insertWordsIntoCategory();
  bool checkIfCategoryExists(std::string &categoryName);
  void analyzeResults(std::vector<std::string> &results);
  void findCategoryNames();
};
