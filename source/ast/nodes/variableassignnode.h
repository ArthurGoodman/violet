#ifndef VARIABLEASSIGNNODE_H
#define VARIABLEASSIGNNODE_H

#include <string>
using namespace std;

#include "node.h"

class VariableAssignNode : public Node {
    string name;
    Node *expr;

public:
    VariableAssignNode(string name, Node *expr);
    ~VariableAssignNode();

    Variant eval(Context *context);
};

#endif // VARIABLEASSIGNNODE_H
