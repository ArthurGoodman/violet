#ifndef BLOCKNODE_H
#define BLOCKNODE_H

#include <list>
using namespace std;

#include "node.h"

class BlockNode : public Node {
    list<Node *> nodes;

public:
    BlockNode(list<Node *> nodes);
    ~BlockNode();

    Variant eval(IContext *context);
};

#endif // BLOCKNODE_H
