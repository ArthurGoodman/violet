#ifndef INTERPRETEDFUNCTION_H
#define INTERPRETEDFUNCTION_H

#include <string>
using namespace std;

#include "function.h"

class Node;
class Context;

class InterpretedFunction : public Function {
    Node *body;
    list<string> params;

public:
    InterpretedFunction(Node *body);
    ~InterpretedFunction();

    Variant call(list<Variant> args);
};

#endif // INTERPRETEDFUNCTION_H
