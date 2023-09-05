#pragma once
#include "User.h"
#include "DAL.h"
#include "Book.h"
#include <iostream>
#include <windows.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>
#include <vector>
#include <nanodbc.h>

using namespace std;

class DAL {
private:
    nanodbc::connection conn;

    void disconnect();

    
    DAL(const string& connectionString) : conn(connectionString) {}

public:
    
   
    DAL(const DAL&) = delete;
    DAL& operator=(const DAL&) = delete;

    static DAL& getInstance() {
        static DAL instance("Driver={ODBC Driver 17 for SQL Server};Server=localhost\\SQLEXPRESS;Database=Library;Trusted_Connection=yes;");
        return instance;
    }

    ~DAL() {}

    bool createUser(const User& user);
    User getUserById(int id);
    bool updateUser(const User& user);
    bool deleteUser(int id);
    bool verifyExistingUser(const User&);
    bool verifyRegisteredUser(const User&);
    vector<User> getUsersByEmail(const std::string& email);
    string ProcessPOST_Request(const User& user);
    string ProcessLOGIN_Request(const User& user);

    bool createBook(const Book& book, const char*);
    bool verifyExistentbooks(const Book& bookverif);

};


