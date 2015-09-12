#include "interpretedfunction.h"

#include "common.h"
#include "variant.h"
#include "node.h"
#include "context.h"
#include "runtime.h"

InterpretedFunction::InterpretedFunction(Node *body)
    : body(body) {
}

InterpretedFunction::~InterpretedFunction() {
    delete body;
}

Variant InterpretedFunction::call(list<Variant> args) {
    Context *context = Runtime::getRoot()->childContext();

    list<Variant>::iterator a = args.begin();

    foreach (i, params)
        context->defineLocal(*i, *a++);

    const Variant &value = body->eval(context);
    delete context;
    return value;
}
