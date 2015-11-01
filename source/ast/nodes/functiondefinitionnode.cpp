#include "functiondefinitionnode.h"

#include "common.h"
#include "variabledefinitionnode.h"
#include "icontext.h"

FunctionDefinitionNode::FunctionDefinitionNode(Variant::Type returnType, string name, list<VariableDefinitionNode *> params, Node *body)
    : returnType(returnType), name(name), params(params), body(body) {
}

FunctionDefinitionNode::~FunctionDefinitionNode() {
    for (Node *node : params)
        delete node;

    delete body;
}

Variant FunctionDefinitionNode::eval(IContext *context) {
    return context->getVoid();
}
