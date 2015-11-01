#include "listnode.h"

#include "icontext.h"
#include "common.h"

ListNode::ListNode(list<Node *> nodes)
    : nodes(nodes) {
}

ListNode::~ListNode() {
    for (Node *node : nodes)
        delete node;
}

Variant ListNode::eval(IContext *context) {
    Variant value = context->getVoid();

    unsigned int i = 0;
    for (Node *node : nodes) {
        value = node->eval(context);

        if (i++ < nodes.size() - 1)
            context->ignore(value);
    }

    return value;
}
