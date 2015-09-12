#include "variableassignnode.h"

#include "icontext.h"

VariableAssignNode::VariableAssignNode(string name, Node *expr)
    : name(name), expr(expr) {
}

VariableAssignNode::~VariableAssignNode() {
    delete expr;
}

Variant VariableAssignNode::eval(IContext *context) {
    Variant value = expr->eval(context);

    if (!context->set(name, value))
        context->defineLocal(name, value);

    return context->get(name);
}
