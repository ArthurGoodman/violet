#include "functioncallnode.h"

#include "context.h"

FunctionCallNode::FunctionCallNode(string name, list<Variant> args)
    : name(name), args(args) {
}

Variant FunctionCallNode::eval(Context *context) {
    return context->getVoid();
}
