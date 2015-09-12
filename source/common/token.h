#ifndef TOKEN_H
#define TOKEN_H

#include <string>
using namespace std;

class Token {
    int id;
    string text;

public:
    Token();
    Token(int id, string text);

    int getId();
    string getText();

    bool operator==(int id);
    bool operator!=(int id);

    Token &operator=(int id);
    Token &operator=(string text);

    Token &operator+=(string text);
    Token &operator+=(char c);
};

#endif // TOKEN_H
