#include "unarynode.h"

#include "icontext.h"
#include "variablenode.h"
#include "io.h"

UnaryNode::UnaryNode(NodeType type, Node *node)
    : type(type), node(node) {
}

UnaryNode::~UnaryNode() {
    delete node;
}

Variant UnaryNode::eval(IContext *context) {
    switch (type) {
    case Plus:
        return context->operation(Variant::Add, context->constant(0), node->eval(context));
    case Minus:
        return context->operation(Variant::Sub, context->constant(0), node->eval(context));

    case Neg:
        return context->logicNot(node->eval(context));

    case PrefDec:
        context->dec(((VariableNode *)node)->getName());
        return node->eval(context);
    case PrefInc:
        context->inc(((VariableNode *)node)->getName());
        return node->eval(context);
    case SuffDec: {
        Variant value = node->eval(context);
        context->dec(((VariableNode *)node)->getName());
        return value;
    }
    case SuffInc: {
        Variant value = node->eval(context);
        context->inc(((VariableNode *)node)->getName());
        return value;
    }

    case Return: {
        return context->getVoid();
    }

    case Print: {
        context->print(node->eval(context));
        return context->getVoid();
    }
    case Println: {
        context->print(node->eval(context));
        context->print(context->constant('\n'));
        return context->getVoid();
    }
    case Scan:
        context->scan(((VariableNode *)node)->getName());
        return node->eval(context);
    case Sizeof: {
        Variant value = node->eval(context);
        return context->size(value);
    }

    default:
        return context->getVoid();
    }
}
