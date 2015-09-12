#ifndef FUNCTIONCALLNODE_H
#define FUNCTIONCALLNODE_H

#include <list>
using namespace std;

#include "node.h"

class FunctionCallNode : public Node {
    string name;
    list<Variant> args;

public:
    FunctionCallNode(string name, list<Variant> args);

    Variant eval(Context *context);
};

#endif // FUNCTIONCALLNODE_H
