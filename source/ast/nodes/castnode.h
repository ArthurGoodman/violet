#ifndef CASTNODE_H
#define CASTNODE_H

#include "node.h"

class CastNode : public Node {
    Variant::Type type;
    Node *expr;

public:
    CastNode(Variant::Type type, Node *expr);
    ~CastNode();

    Variant eval(IContext *context);
};

#endif // CASTNODE_H
