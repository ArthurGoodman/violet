#ifndef WHILENODE_H
#define WHILENODE_H

#include "node.h"

class WhileNode : public Node {
    Node *condition, *body;

public:
    WhileNode(Node *condition, Node *body);
    ~WhileNode();

    Variant eval(IContext *context);
};

#endif // WHILENODE_H
