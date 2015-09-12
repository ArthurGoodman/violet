#ifndef LISTNODE_H
#define LISTNODE_H

#include <list>
using namespace std;

#include "node.h"

class ListNode : public Node {
    list<Node *> nodes;

public:
    ListNode(list<Node *> nodes);
    ~ListNode();

    Variant eval(Context *context);
};

#endif // LISTNODE_H
