#ifndef VARIABLEDEFINITIONNODE_H
#define VARIABLEDEFINITIONNODE_H

#include <string>
#include <list>
using namespace std;

#include "node.h"

class VariableDefinitionNode : public Node {
    Variant::Type type;
    list<pair<string, Node *> > definitions;
    bool isConst;

public:
    VariableDefinitionNode(Variant::Type type, list<pair<string, Node *> > definitions, bool isConst);
    ~VariableDefinitionNode();

    Variant eval(IContext *context);
};

#endif // VARIABLEDEFINITIONNODE_H
