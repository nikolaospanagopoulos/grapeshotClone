#include "Database.h"
void Database::connectToDb() {
  driver = get_driver_instance();
  con = driver->connect("tcp://127.0.0.1:3306", "root", "root");
  stmt = con->createStatement();
  res = stmt->executeQuery("SELECT 'Hello World!' AS _message");
  while (res->next()) {
    std::cout << "\t... MySQL replies: ";
    /* Access column data by alias or column name */
    std::cout << res->getString("_message") << std::endl;
    std::cout << "\t... MySQL says it again: ";
    /* Access column data by numeric offset, 1 is the first column */
    std::cout << res->getString(1) << std::endl;
  }
}
