
#include "Database.h"
#include "CategoriesDownloader.h"
#include "Exception.h"
#include "JsonParser.h"

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

void Database::showAllInTable(std::string &&tableName) {
  try {

    stmt = con->createStatement();

    std::string query{"SELECT * FROM "};

    query.append(tableName);
    res = stmt->executeQuery(query);
    sql::ResultSetMetaData *res_meta = res->getMetaData();

    int columns = res_meta->getColumnCount();

    while (res->next()) {
      for (int i = 1; i <= columns; i++) {
        std::cout << res->getString(i) << "|";
      }
    }
  } catch (sql::SQLException &e) {
    std::cerr << e.what() << std::endl;
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
    std::cout << query << std::endl;

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
