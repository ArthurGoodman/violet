#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <list>
using namespace std;

class Token;

class Lexer {
public:
    virtual ~Lexer();

    virtual list<Token> lex(string source) = 0;
};

#endif // LEXER_H
