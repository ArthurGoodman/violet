#include "variableassignnode.h"

#include "context.h"

VariableAssignNode::VariableAssignNode(string name, Node *expr)
    : name(name), expr(expr) {
}

VariableAssignNode::~VariableAssignNode() {
    delete expr;
}

Variant VariableAssignNode::eval(Context *context) {
    Variant value = expr->eval(context);

    if (!context->set(name, value))
        context->defineLocal(name, value);

    return context->get(name);
}
