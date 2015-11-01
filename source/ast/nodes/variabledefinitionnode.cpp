#include "variabledefinitionnode.h"

#include "icontext.h"
#include "common.h"

VariableDefinitionNode::VariableDefinitionNode(Variant::Type type, list<pair<string, Node *>> definitions, bool isConst)
    : type(type), definitions(definitions), isConst(isConst) {
}

VariableDefinitionNode::~VariableDefinitionNode() {
    for (auto &def : definitions)
        delete def.second;
}

Variant VariableDefinitionNode::eval(IContext *context) {
    for (auto &def : definitions) {
        if (context->hasLocal(def.first)) {
            context->error("variable '" + def.first + "' is already defined");
            return context->getVoid();
        }

        Variant value = def.second ? def.second->eval(context) : context->constant(0);

        if (type != Variant::Undefined)
            value = context->cast(value, type);

        context->defineLocal(def.first, value, isConst);
    }

    return context->getVoid();
}
