#include "fornode.h"

#include "icontext.h"
#include "breakexception.h"
#include "continueexception.h"

ForNode::ForNode(Node *preffix, Node *condition, Node *suffix, Node *body)
    : preffix(preffix), condition(condition), suffix(suffix), body(body) {
}

ForNode::~ForNode() {
    delete preffix;
    delete condition;
    delete suffix;
    delete body;
}

Variant ForNode::eval(IContext *context) {
    context = context->childContext();
    context->For(preffix, condition, suffix, body);

    Variant Void = context->getVoid();
    delete context;
    return Void;
}
