#include "castnode.h"

#include "icontext.h"

CastNode::CastNode(Variant::Type type, Node *expr)
    : type(type), expr(expr) {
}

CastNode::~CastNode() {
    delete expr;
}

Variant CastNode::eval(IContext *context) {
    return context->cast(expr->eval(context), type);
}
