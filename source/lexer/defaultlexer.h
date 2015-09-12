#ifndef DEFAULTLEXER_H
#define DEFAULTLEXER_H

#include <vector>

#include "lexer.h"
#include "token.h"

class DefaultLexer : public Lexer {
    static vector<string> operators;
    static vector<string> keywords;

    static vector<string> tokenTypes;

    list<Token> tokens;

    string source;
    Token token;
    int pos;

public:
    list<Token> lex(string source);

private:
    void error(string message);
    void scan();
    void skipSpaces();
    const char &at(int pos);
};

#endif // DEFAULTLEXER_H
