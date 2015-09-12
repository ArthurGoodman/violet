#ifndef VARIABLENODE_H
#define VARIABLENODE_H

#include <string>
using namespace std;

#include "node.h"

class VariableNode : public Node {
    string name;

public:
    VariableNode(string name);

    string getName();

    Variant eval(IContext *context);
};

#endif // VARIABLENODE_H
