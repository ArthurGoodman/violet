#ifndef BINARYNODE_H
#define BINARYNODE_H

#include "node.h"

class BinaryNode : public Node {
public:
    enum NodeType {
        Plus,
        Minus,
        Multiply,
        Divide,
        Mod,

        Lt,
        Gt,
        Le,
        Ge,
        Eq,
        Ne,

        And,
        Or,
    };

private:
    NodeType type;
    Node *left, *right;

public:
    BinaryNode(NodeType type, Node *left, Node *right);
    ~BinaryNode();

    Variant eval(IContext *context);
};

#endif // BINARYNODE_H
