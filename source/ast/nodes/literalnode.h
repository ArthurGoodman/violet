#ifndef LITERALNODE_H
#define LITERALNODE_H

#include "node.h"

class LiteralNode : public Node {
    Variant value;

public:
    LiteralNode(Variant value);

    Variant eval(Context *context);
};

#endif // LITERALNODE_H
