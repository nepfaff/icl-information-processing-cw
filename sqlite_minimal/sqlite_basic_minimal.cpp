#include <iostream>
#include <stdlib.h> 
#include <sqlite3.h>

using namespace std;

// called on data that is returned from sqlite3_exec 
static int printCallback(void *unused, int count, char **data, char **columns) {
   for (int i=0; i<count; i++) {
      cout << "The data in column " << columns[i] << " is: " << data[i] << endl;
   }

   cout << endl;

   return 0;
}

void fatalError(sqlite3 *db, char *zErrMsg) {
   sqlite3_free(zErrMsg);
   sqlite3_close(db);
   exit(EXIT_FAILURE);
}

int main() {
   char *zErrMsg = nullptr;
   sqlite3 *db;

   // establish connection
   int rc = sqlite3_open("test_basic.db", &db);
   if (rc != SQLITE_OK) {
      cerr << "Error: Failed to open database: " << sqlite3_errmsg(db) << endl;
      fatalError(db, nullptr);
   } else {
      cout << "Status: Opened database successfully" << endl;
   }

   // create table
   char *sql = (char*)"CREATE TABLE IF NOT EXISTS coffees ("  \
      "id         INTEGER PRIMARY KEY AUTOINCREMENT   NOT NULL," \
      "name       TEXT                                NOT NULL," \
      "variety    TEXT                                NOT NULL," \
      "origin     TEXT                                NOT NULL);";
   rc = sqlite3_exec(db, sql, nullptr, 0, &zErrMsg);
   if (rc != SQLITE_OK) {
      cerr << "Error: Failed to create table: " << zErrMsg << endl;
      fatalError(db, zErrMsg);
   } else {
      cout << "Status: Created table successfully" << endl;
   }

   // insert into table
   sql = (char*)"INSERT INTO coffees (name, variety, origin) " \
      "VALUES ('El Pariso', 'Catuai', 'Colombia');" \
      "INSERT INTO coffees (name, variety, origin) " \
      "VALUES ('Sweetshop', 'Blend', 'Rwanda');" \
      "INSERT INTO coffees (name, variety, origin) " \
      "VALUES ('Basic', 'Bourbon', 'Brazil');";
   rc = sqlite3_exec(db, sql, nullptr, 0, &zErrMsg);
   if (rc != SQLITE_OK) {
      cerr << "Error: Failed to insert into table: " << zErrMsg << endl;
      fatalError(db, zErrMsg);
   } else {
      cout << "Status: Inserted into table successfully" << endl;
   }

   // retrieve values from table
   sql = (char*)"SELECT * FROM coffees;";
   rc = sqlite3_exec(db, sql, printCallback, 0, &zErrMsg);
   if (rc != SQLITE_OK) {
      cerr << "Error: Failed to retrieve data from table: " << zErrMsg << endl;
      fatalError(db, zErrMsg);
   } else {
      cout << "Status: Retrieved data from table successfully" << endl;
   }

   sqlite3_close(db);
}
