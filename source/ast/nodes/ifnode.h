#ifndef IFNODE_H
#define IFNODE_H

#include "node.h"

class IfNode : public Node {
    Node *condition, *body, *elseBody;

public:
    IfNode(Node *condition, Node *body, Node *elseBody);
    ~IfNode();

    Variant eval(IContext *context);
};

#endif // IFNODE_H
