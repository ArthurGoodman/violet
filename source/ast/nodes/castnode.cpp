#include "castnode.h"

#include "context.h"

CastNode::CastNode(Variant::Type type, Node *expr)
    : type(type), expr(expr) {
}

CastNode::~CastNode() {
    delete expr;
}

Variant CastNode::eval(Context *context) {
    return context->cast(expr->eval(context), type);
}
