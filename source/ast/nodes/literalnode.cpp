#include "literalnode.h"

#include "context.h"

LiteralNode::LiteralNode(Variant value)
    : value(value) {
}

Variant LiteralNode::eval(Context *context) {
    return context->constant(value);
}
