#include "literalnode.h"

#include "icontext.h"

LiteralNode::LiteralNode(Variant value)
    : value(value) {
}

Variant LiteralNode::eval(IContext *context) {
    return context->constant(value);
}
