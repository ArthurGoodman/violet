#ifndef NODE_H
#define NODE_H

#include "variant.h"

class Context;

class Node {
public:
    virtual ~Node();

    virtual Variant eval(Context *context) = 0;
};

#endif // NODE_H
