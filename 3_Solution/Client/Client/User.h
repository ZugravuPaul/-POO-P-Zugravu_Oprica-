#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

using namespace std;

class User {
private:
    int id=0;
    string username;
    string password;
    string email;
public:
    User(const string& username, const string& pass, const string& email) : username(username), email(email), password(pass) {}
    User() {}
    std::string SerializeUser();
    void Deserialize(const std::string& serializedUser);
};