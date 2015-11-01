#include "interpretedfunction.h"

#include "common.h"
#include "variant.h"
#include "node.h"
#include "icontext.h"
#include "runtime.h"

InterpretedFunction::InterpretedFunction(Node *body)
    : body(body) {
}

InterpretedFunction::~InterpretedFunction() {
    delete body;
}

Variant InterpretedFunction::call(list<Variant> args) {
    IContext *context = Runtime::getRoot()->childContext();

    list<Variant>::iterator a = args.begin();

    for (string &param : params)
        context->defineLocal(param, *a++);

    const Variant &value = body->eval(context);
    delete context;
    return value;
}
