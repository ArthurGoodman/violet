#include "binarynode.h"

#include "icontext.h"

BinaryNode::BinaryNode(NodeType type, Node *left, Node *right)
    : type(type), left(left), right(right) {
}

BinaryNode::~BinaryNode() {
    delete left;
    delete right;
}

Variant BinaryNode::eval(IContext *context) {
    const Variant &lv = left->eval(context), &rv = right->eval(context);

    switch (type) {
    case Plus:
        return context->operation(Variant::Add, lv, rv);
    case Minus:
        return context->operation(Variant::Sub, lv, rv);
    case Multiply:
        return context->operation(Variant::Mul, lv, rv);
    case Divide:
        return context->operation(Variant::Div, lv, rv);
    case Mod:
        return context->operation(Variant::Mod, lv, rv);

    case Lt:
        return context->operation(Variant::Lt, lv, rv);
    case Gt:
        return context->operation(Variant::Gt, lv, rv);
    case Le:
        return context->operation(Variant::Le, lv, rv);
    case Ge:
        return context->operation(Variant::Ge, lv, rv);
    case Eq:
        return context->operation(Variant::Eq, lv, rv);
    case Ne:
        return context->operation(Variant::Ne, lv, rv);

    case And:
        return context->logicAnd(lv, rv);
    case Or:
        return context->logicOr(lv, rv);

    default:
        return context->getVoid();
    }
}

