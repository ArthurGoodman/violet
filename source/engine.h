#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include <list>
using namespace std;

class ILexer;
class IParser;
class Compiler;
class VirtualMachine;

class Engine {
    enum Action {
        //None = -1,

        CompileAndRun,
        //LoadAndRun,
        Interpret,
        //Compile,
        //Disassemble
    };

    static list<string> args;

    static Action action;

    static string input;
    static string output;

    static ILexer *lexer;
    static IParser *parser;
    static Compiler *compiler;
    static VirtualMachine *virtualMachine;

    static bool error;

public:
    static void init(int argc, char **argv);
    static void release();

    static void run();

private:
    static void defaults();
    static void parseArgs();
};

#endif // ENGINE_H
