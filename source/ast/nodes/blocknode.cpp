#include "blocknode.h"

#include "icontext.h"
#include "common.h"

BlockNode::BlockNode(list<Node *> nodes)
    : nodes(nodes) {
}

BlockNode::~BlockNode() {
    for (Node *node : nodes)
        delete node;
}

Variant BlockNode::eval(IContext *context) {
    context = context->childContext();

    for (Node *node : nodes)
        context->ignore(node->eval(context));

    Variant Void = context->getVoid();
    delete context;
    return Void;
}
