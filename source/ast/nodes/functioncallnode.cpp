#include "functioncallnode.h"

#include "icontext.h"

FunctionCallNode::FunctionCallNode(string name, list<Variant> args)
    : name(name), args(args) {
}

Variant FunctionCallNode::eval(IContext *context) {
    return context->getVoid();
}
