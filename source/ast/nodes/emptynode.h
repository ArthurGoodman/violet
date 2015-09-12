#ifndef EMPTYNODE_H
#define EMPTYNODE_H

#include "node.h"

class EmptyNode : public Node {
public:
    Variant eval(IContext *context);
};

#endif // EMPTYNODE_H
