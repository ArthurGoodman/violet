#ifndef DEFAULTPARSER_H
#define DEFAULTPARSER_H

#include <string>

#include "iparser.h"
#include "variant.h"

class Parser : public IParser {
    list<Token> tokens;
    list<Token>::iterator token;

public:
    Node *parse(list<Token> tokens);

private:
    void error(string message);

    bool check(int id);
    bool accept(int id);

    void getToken();

    Node *program();
    Node *statement();
    Node *definition();
    Node *oper();
    Node *expr();
    Node *logicOr();
    Node *logicAnd();
    Node *equality();
    Node *relation();
    Node *addSub();
    Node *mulDiv();
    Node *preffix();
    Node *suffix();
    Node *term();

    bool isType();
    Variant::Type toType();
};

#endif // DEFAULTPARSER_H
