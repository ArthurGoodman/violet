#include "runtime.h"

#include "runtimecontext.h"
#include "compilercontext.h"

Context *Runtime::root;

void Runtime::initializeInterpreter() {
    root = new RuntimeContext;
}

void Runtime::initializeCompiler(Compiler *compiler) {
    root = new CompilerContext(compiler);
}

void Runtime::release() {
    delete root;
}

Context *Runtime::getRoot() {
    return root;
}
