#include "emptynode.h"

#include "context.h"

Variant EmptyNode::eval(Context *context) {
    context->empty();
    return context->getVoid();
}
