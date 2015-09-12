#ifndef PARSER_H
#define PARSER_H

#include <list>
using namespace std;

class Token;
class Node;

class IParser {
public:
    virtual ~IParser();

    virtual Node *parse(list<Token> tokens) = 0;
};

#endif // PARSER_H
