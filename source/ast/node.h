#ifndef NODE_H
#define NODE_H

#include "variant.h"

class IContext;

class Node {
public:
    virtual ~Node();

    virtual Variant eval(IContext *context) = 0;
};

#endif // NODE_H
