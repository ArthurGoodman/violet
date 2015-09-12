#ifndef DONODE_H
#define DONODE_H

#include "node.h"

class DoNode : public Node {
    Node *body, *condition;

public:
    DoNode(Node *body, Node *condition);
    ~DoNode();

    Variant eval(Context *context);
};

#endif // DONODE_H
