#ifndef RUNTIME_H
#define RUNTIME_H

class Context;
class Compiler;

class Runtime {
    static Context *root;

public:
    static void initializeInterpreter();
    static void initializeCompiler(Compiler *compiler);
    static void release();

    static Context *getRoot();
};

#endif // RUNTIME_H
