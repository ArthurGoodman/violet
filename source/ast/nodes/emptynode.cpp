#include "emptynode.h"

#include "icontext.h"

Variant EmptyNode::eval(IContext *context) {
    context->empty();
    return context->getVoid();
}
