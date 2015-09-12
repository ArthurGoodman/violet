#ifndef RUNTIME_H
#define RUNTIME_H

class IContext;
class Compiler;

class Runtime {
    static IContext *root;

public:
    static void initializeInterpreter();
    static void initializeCompiler(Compiler *compiler);
    static void release();

    static IContext *getRoot();
};

#endif // RUNTIME_H
