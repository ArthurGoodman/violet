#include "variablenode.h"

#include "context.h"

VariableNode::VariableNode(string name)
    : name(name) {
}

string VariableNode::getName() {
    return name;
}

Variant VariableNode::eval(Context *context) {
    return context->get(name);
}
