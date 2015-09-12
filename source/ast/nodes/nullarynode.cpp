#include "nullarynode.h"

#include "icontext.h"
#include "breakexception.h"
#include "continueexception.h"

NullaryNode::NullaryNode(NodeType type)
    : type(type) {
}

Variant NullaryNode::eval(IContext *context) {
    switch (type) {
    case Break:
        throw new BreakException;
    case Continue:
        throw new ContinueException;
    }

    return context->getVoid();
}
