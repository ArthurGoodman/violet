#include "blocknode.h"

#include "icontext.h"
#include "common.h"

BlockNode::BlockNode(list<Node *> nodes)
    : nodes(nodes) {
}

BlockNode::~BlockNode() {
    foreach (i, nodes)
        delete *i;
}

Variant BlockNode::eval(IContext *context) {
    context = context->childContext();

    foreach (i, nodes)
        context->ignore((*i)->eval(context));

    Variant Void = context->getVoid();
    delete context;
    return Void;
}
