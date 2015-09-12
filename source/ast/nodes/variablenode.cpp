#include "variablenode.h"

#include "icontext.h"

VariableNode::VariableNode(string name)
    : name(name) {
}

string VariableNode::getName() {
    return name;
}

Variant VariableNode::eval(IContext *context) {
    return context->get(name);
}
