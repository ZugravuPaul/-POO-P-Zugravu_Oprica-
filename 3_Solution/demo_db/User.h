#pragma once
#include <string>


using namespace std;

class User {
private:
    int id=0;
    string nume, prenume;
    string username;
    string password;
    string email;
public:
    friend class DAL;
    User(const string& nume, const string& prenume,const string& username, const string& pass, const string& email) :
        nume(nume), prenume(prenume),username(username), password(pass),email(email) {}
    User(){}
    User(const string& username, const string& pass): username(username),password(pass) {}
    
    
};