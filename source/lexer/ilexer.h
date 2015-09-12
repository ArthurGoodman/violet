#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <list>
using namespace std;

class Token;

class ILexer {
public:
    virtual ~ILexer();

    virtual list<Token> lex(string source) = 0;
};

#endif // LEXER_H
