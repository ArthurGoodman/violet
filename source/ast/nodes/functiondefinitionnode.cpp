#include "functiondefinitionnode.h"

#include "common.h"
#include "variabledefinitionnode.h"
#include "context.h"

FunctionDefinitionNode::FunctionDefinitionNode(Variant::Type returnType, string name, list<VariableDefinitionNode *> params, Node *body)
    : returnType(returnType), name(name), params(params), body(body) {
}

FunctionDefinitionNode::~FunctionDefinitionNode() {
    foreach(i, params)
        delete *i;

    delete body;
}

Variant FunctionDefinitionNode::eval(Context *context) {
    return context->getVoid();
}
