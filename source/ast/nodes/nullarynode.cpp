#include "nullarynode.h"

#include "context.h"
#include "breakexception.h"
#include "continueexception.h"

NullaryNode::NullaryNode(NodeType type)
    : type(type) {
}

Variant NullaryNode::eval(Context *context) {
    switch (type) {
    case Break:
        throw new BreakException;
    case Continue:
        throw new ContinueException;
    }

    return context->getVoid();
}
