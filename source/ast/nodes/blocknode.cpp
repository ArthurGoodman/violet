#include "blocknode.h"

#include "context.h"
#include "common.h"

BlockNode::BlockNode(list<Node *> nodes)
    : nodes(nodes) {
}

BlockNode::~BlockNode() {
    foreach (i, nodes)
        delete *i;
}

Variant BlockNode::eval(Context *context) {
    context = context->childContext();

    foreach (i, nodes)
        context->ignore((*i)->eval(context));

    Variant Void = context->getVoid();
    delete context;
    return Void;
}
