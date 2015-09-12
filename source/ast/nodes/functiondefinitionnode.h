#ifndef FUNCTIONDEFINITIONNODE_H
#define FUNCTIONDEFINITIONNODE_H

#include <list>
using namespace std;

#include "node.h"
class VariableDefinitionNode;

class FunctionDefinitionNode : public Node {
    Variant::Type returnType;
    string name;
    list<VariableDefinitionNode *> params;
    Node *body;

public:
    FunctionDefinitionNode(Variant::Type returnType, string name, list<VariableDefinitionNode *> params, Node *body);
    ~FunctionDefinitionNode();

    Variant eval(IContext *context);
};

#endif // FUNCTIONDEFINITIONNODE_H
