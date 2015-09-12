#ifndef NULLARYNODE_H
#define NULLARYNODE_H

#include "node.h"

class NullaryNode : public Node {
public:
    enum NodeType {
        Break,
        Continue
    };

private:
    NodeType type;

public:
    NullaryNode(NodeType type);

    Variant eval(IContext *context);
};

#endif // NULLARYNODE_H
