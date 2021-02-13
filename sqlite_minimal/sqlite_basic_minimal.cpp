#include <iostream>
#include <stdlib.h> 
#include <sqlite3.h>

using namespace std;

int main() {
   sqlite3 *db;

   int dbConnection = sqlite3_open("test_basic.db", &db);

   if (dbConnection) {
      cerr << "Error: Failed to open database: " << sqlite3_errmsg(db) << endl;
      exit (EXIT_FAILURE);
   } else {
      cerr << "Status: Opened database successfully" << endl;
   }

   sqlite3_close(db);
}
