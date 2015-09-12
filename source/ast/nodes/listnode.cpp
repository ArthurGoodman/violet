#include "listnode.h"

#include "context.h"
#include "common.h"

ListNode::ListNode(list<Node *> nodes)
    : nodes(nodes) {
}

ListNode::~ListNode() {
    foreach (i, nodes)
        delete *i;
}

Variant ListNode::eval(Context *context) {
    Variant value = context->getVoid();

    foreach (i, nodes) {
        value = (*i)->eval(context);

        if (next(i) != nodes.end())
            context->ignore(value);
    }

    return value;
}
