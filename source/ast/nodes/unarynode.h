#ifndef UNARYNODE_H
#define UNARYNODE_H

#include "node.h"

class UnaryNode : public Node {
public:
    enum NodeType {
        Plus,
        Minus,

        Neg,

        PrefDec,
        PrefInc,
        SuffDec,
        SuffInc,

        Return,

        Print,
        Println,
        Scan,
        Sizeof
    };

private:
    NodeType type;
    Node *node;

public:
    UnaryNode(NodeType type, Node *node);
    ~UnaryNode();

    Variant eval(Context *context);
};

#endif // UNARYNODE_H
