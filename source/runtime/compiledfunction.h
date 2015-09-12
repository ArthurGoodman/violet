#ifndef COMPILEDFUNCTION_H
#define COMPILEDFUNCTION_H

#include "function.h"

class CompiledFunction : public Function {
public:
    Variant call(list<Variant> args);
};

#endif // COMPILEDFUNCTION_H
