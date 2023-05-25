#pragma once
#include <string>


using namespace std;

class DetCarti {
private:
    int id = 0;
    int IdUser;
    int IdCarti;

public:
    friend class DAL;
    DetCarti(const int& IdUser, const int& IdCarti) :
        IdUser(IdUser), IdCarti(IdCarti) {}
    DetCarti() {}


};