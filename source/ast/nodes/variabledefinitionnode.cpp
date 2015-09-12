#include "variabledefinitionnode.h"

#include "context.h"
#include "common.h"

VariableDefinitionNode::VariableDefinitionNode(Variant::Type type, list<pair<string, Node *>> definitions, bool isConst)
    : type(type), definitions(definitions), isConst(isConst) {
}

VariableDefinitionNode::~VariableDefinitionNode() {
    foreach (i, definitions)
        delete i->second;
}

Variant VariableDefinitionNode::eval(Context *context) {
    foreach (i, definitions) {
        if (context->hasLocal(i->first)) {
            context->error("variable '" + i->first + "' is already defined");
            return context->getVoid();
        }

        Variant value = i->second ? i->second->eval(context) : context->constant(0);

        if (type != Variant::Undefined)
            value = context->cast(value, type);

        context->defineLocal(i->first, value, isConst);
    }

    return context->getVoid();
}
