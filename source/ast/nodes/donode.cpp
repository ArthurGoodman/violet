#include "donode.h"

#include "icontext.h"
#include "breakexception.h"
#include "continueexception.h"

DoNode::DoNode(Node *body, Node *condition)
    : body(body), condition(condition) {
}

DoNode::~DoNode() {
    delete body;
    delete condition;
}

Variant DoNode::eval(IContext *context) {
    context = context->childContext();
    context->Do(body, condition);

    Variant Void = context->getVoid();
    delete context;
    return Void;
}
