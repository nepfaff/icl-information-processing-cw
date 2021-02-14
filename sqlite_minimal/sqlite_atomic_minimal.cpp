#include <iostream>
#include <stdlib.h> 
#include <sqlite3.h>
#include <functional>
#include <stdexcept>
#include <string.h>

using namespace std;

void transaction(sqlite3 *db, const function<void(sqlite3 *db, char *zErrMsg)> &f) {
    if (!db) {
        throw invalid_argument("transaction: db argument invalid");
    }

    // start transaction
    sqlite3_exec(db, "BEGIN", 0, 0, 0);
    
    char *zErrMsg = nullptr;
    try {
        f(db, zErrMsg);
    }
    catch(exception &e) {
        sqlite3_free(zErrMsg);

        // rollback
        sqlite3_exec(db, "ROLLBACK", 0, 0, 0);
        
        throw runtime_error("transaction: transaction failed, rolled back db: " + (string)e.what());
    }

    // commit transaction
    sqlite3_exec(db, "COMMIT", 0, 0, 0);

    cout << "Status: Transaction completed successfully" << endl;
}

// called on data that is returned from sqlite3_exec 
static int printCallback(void *unused, int count, char **data, char **columns) {
   for (int i=0; i<count; i++) {
      cout << "The data in column " << columns[i] << " is: " << data[i] << endl;
   }

   cout << endl;

   return 0;
}

int main () {
    sqlite3 *db;
    char *zErrMsg;

    try {
        // establish connection
        int rc = sqlite3_open("test_atomic.db", &db);
        if (rc != SQLITE_OK) {
            throw runtime_error("main: failed to open database: " + (string)sqlite3_errmsg(db));
        } else {
            cout << "Status: Opened database successfully" << endl;
        }

        // wrap everything into a transaction
        transaction(db, [](sqlite3 *db, char *zErrMsg) {
            // create table
            char *sql = (char*)"CREATE TABLE IF NOT EXISTS coffees ("  \
                "id         INTEGER PRIMARY KEY AUTOINCREMENT   NOT NULL," \
                "name       TEXT                                NOT NULL," \
                "variety    TEXT                                NOT NULL," \
                "origin     TEXT                                NOT NULL);";
            int rc = sqlite3_exec(db, sql, nullptr, 0, &zErrMsg);
            if (rc != SQLITE_OK) {
                throw runtime_error("main: failed to create coffees table: " + (string)zErrMsg);
            } else {
                cout << "Status: Created coffees table successfully" << endl;
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
                throw runtime_error("main: failed to insert into coffees table: " + (string)zErrMsg);
            } else {
                cout << "Status: Inserted into coffees table successfully" << endl;
            }
        });

        // retrieve values from table
        char *sql = (char*)"SELECT * FROM coffees;";
        rc = sqlite3_exec(db, sql, printCallback, 0, &zErrMsg);
        if (rc != SQLITE_OK) {
            throw runtime_error("main: failed to retrieve data from coffees table: " + (string)zErrMsg);
        } else {
            cout << "Status: Retrieved data from table successfully" << endl;
        }
    }
    catch(exception &e) {
        cerr << e.what() << endl;
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    sqlite3_close(db);
    return 0;
}
