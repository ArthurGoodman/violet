#include "ifnode.h"

#include "icontext.h"

IfNode::IfNode(Node *condition, Node *body, Node *elseBody)
    : condition(condition), body(body), elseBody(elseBody) {
}

IfNode::~IfNode() {
    delete condition;
    delete body;

    if (elseBody)
        delete elseBody;
}

Variant IfNode::eval(IContext *context) {
    context = context->childContext();
    context->If(condition, body, elseBody);

    Variant Void = context->getVoid();
    delete context;
    return Void;
}
