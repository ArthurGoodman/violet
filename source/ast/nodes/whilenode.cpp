#include "whilenode.h"

#include "icontext.h"
#include "breakexception.h"
#include "continueexception.h"

WhileNode::WhileNode(Node *condition, Node *body)
    : condition(condition), body(body) {
}

WhileNode::~WhileNode() {
    delete condition;
    delete body;
}

Variant WhileNode::eval(IContext *context) {
    context = context->childContext();
    context->While(condition, body);

    Variant Void = context->getVoid();
    delete context;
    return Void;
}
