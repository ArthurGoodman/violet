#ifndef FORNODE_H
#define FORNODE_H

#include "node.h"

class ForNode : public Node {
    Node *preffix, *condition, *suffix, *body;

public:
    ForNode(Node *preffix, Node *condition, Node *suffix, Node *body);
    ~ForNode();

    Variant eval(IContext *context);
};

#endif // FORNODE_H
