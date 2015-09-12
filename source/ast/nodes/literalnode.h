#ifndef LITERALNODE_H
#define LITERALNODE_H

#include "node.h"

class LiteralNode : public Node {
    Variant value;

public:
    LiteralNode(Variant value);

    Variant eval(IContext *context);
};

#endif // LITERALNODE_H
