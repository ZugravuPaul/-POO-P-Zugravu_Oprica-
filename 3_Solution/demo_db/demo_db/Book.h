#pragma once
#include <string>


using namespace std;


class Book {
private:
    static int id_gen;
    int id = 0;
    string Titlu;
    string Autor;
    string An_publicare;
    
public:
    friend class DAL;
    Book(const string& Titlu, const string& Autor, const string& An_publicare) :
        Titlu(Titlu), Autor(Autor), An_publicare(An_publicare) {
        id = Book::id_gen++;
    }
    Book() { id = Book::id_gen++; }


};

