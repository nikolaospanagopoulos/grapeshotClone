
#include "Database.h"
#include "CategoriesDownloader.h"
#include "Exception.h"
#include "JsonParser.h"
#include <array>

Database::~Database() {
  delete con;
  delete stmt;
  delete res;
}

Database::Database() {
  driver = get_driver_instance();
  con = driver->connect("tcp://127.0.0.1:3306", "root", "root");
  con->setSchema("word_categories");
}

void Database::showAllInTable(std::string &tableName) {
  try {

    stmt = con->createStatement();

    std::string whatToSelect = tableName == "words"        ? "text"
                               : tableName == "categories" ? "name"
                                                           : "*";
    std::string query{"SELECT "};
    query.append(whatToSelect);
    query += " FROM ";

    query.append(tableName);
    res = stmt->executeQuery(query);
    sql::ResultSetMetaData *res_meta = res->getMetaData();

    int columns = res_meta->getColumnCount();

    std::cout << query << std::endl;
    while (res->next()) {
      for (int i = 1; i <= columns; i++) {
        std::cout << "| " << res->getString(i) << " |" << std::endl;
      }
    }
  } catch (sql::SQLException &e) {
    throw CustomException(const_cast<char *>("couldnt find database name"));
  }
}

void Database::createAcategory(std::string &categoryName) {

  try {

    bool categoryExixsts = checkIfCategoryExists(categoryName);
    if (categoryExixsts) {
      throw CustomException(const_cast<char *>("already exists"));
    }

    std::string query{"INSERT IGNORE INTO categories (name) VALUES "};

    query.append("(\"" + categoryName + "\");");
    res = stmt->executeQuery(query);

  } catch (sql::SQLException &e) {
    std::cerr << e.what() << std::endl;
  }
}

void Database::insertWordsIntoCategory() {
  try {

    std::cout << "category name: " << std::endl;

    std::string categoryName{};

    std::cin >> categoryName;

    bool categoryExixsts = checkIfCategoryExists(categoryName);

    if (!categoryExixsts) {
      throw CustomException(
          const_cast<char *>("this category needs to be created first"));
    }

    std::cout << "what theme would you like to add?" << std::endl;

    std::string theme{};

    std::cin >> theme;

    CategoriesDownloader categoriesDownloader;

    std::string result = categoriesDownloader.requestData(theme);

    JsonParser jsonparser;

    json JsonResult = jsonparser.setJsonObj(result);

    std::vector<std::string> resultsVec =
        jsonparser.createWordVector(JsonResult);

    std::string queryToGetId = "SELECT category_id FROM categories WHERE name=";

    queryToGetId.append("\"" + categoryName + "\"");
    res = stmt->executeQuery(queryToGetId);
    sql::ResultSetMetaData *res_meta = res->getMetaData();
    int columns = res_meta->getColumnCount();
    std::string categoryId{};
    while (res->next()) {
      for (int i = 1; i <= columns; i++) {
        categoryId = res->getString(i);
      }
    }

    std::string queryToAddWords =
        "INSERT IGNORE INTO words (category_id,text) VALUES ";

    for (auto &val : resultsVec) {

      queryToAddWords.append("(" + categoryId + "," + "\"" + val + "\"), ");
    }
    queryToAddWords.pop_back();
    queryToAddWords.pop_back();
    queryToAddWords.append(";");

    std::cout << queryToAddWords << std::endl;
    res = stmt->executeQuery(queryToAddWords);
    std::cout << "done" << std::endl;
  } catch (sql::SQLException &e) {
    std::cerr << e.what() << std::endl;
  }
}

bool Database::checkIfCategoryExists(std::string &categoryName) {
  stmt = con->createStatement();

  std::string testName{"SELECT category_id FROM categories WHERE name="};

  testName.append("\"" + categoryName + "\"");

  res = stmt->executeQuery(testName);

  int columns = res->rowsCount();

  if (columns > 0) {

    return true;
  }
  return false;
}

void Database::analyzeResults(std::vector<std::string> &results) {

  stmt = con->createStatement();

  std::string statement = {"SELECT category_id FROM words WHERE "};

  if (results.size() == 0) {
    throw CustomException(const_cast<char *>("results to check are empty"));
  }

  for (auto &val : results) {

    std::string text = "text LIKE ";

    std::string orSql = " OR ";
    statement.append(text + "\"" + val + "\"" + orSql);
  }
  auto wordToRemove = statement.find_last_of("OR");

  statement.erase(wordToRemove - 1);

  statement.append(";");

  res = stmt->executeQuery(statement);
  sql::ResultSetMetaData *res_meta = res->getMetaData();

  int columns = res_meta->getColumnCount();

  if (columns > 0) {
    while (res->next()) {
      for (int i = 1; i <= columns; i++) {

        resultsNumVec.push_back(res->getString(i));
      }
    }
    findCategoryNames();
  }
}

void Database::findCategoryNames() {

  if (resultsNumVec.size() == 0) {
    throw CustomException(const_cast<char *>("no results"));
  }

  for (auto &val : resultsNumVec) {
    std::string statement{"SELECT name FROM categories WHERE category_id ="};
    statement.append(val);
    statement += ";";
    res = stmt->executeQuery(statement);
    sql::ResultSetMetaData *res_meta = res->getMetaData();

    int columns = res_meta->getColumnCount();
    if (columns == 0) {
      throw CustomException(const_cast<char *>("no results in db"));
    }

    while (res->next()) {
      for (int i = 1; i <= columns; i++) {

        resultsMap[res->getString(i)]++;
      }
    }
  }
  for (auto pair : resultsMap) {
    std::cout << std::endl;
    std::string reference{};
    if (pair.second == 1) {

      reference = "references ";
    } else {
      reference = "reference ";
    }

    std::cout << "from the words tested ," << pair.second << " " << reference
              << pair.first << std::endl;
  }
}
