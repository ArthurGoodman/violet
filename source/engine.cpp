#include "engine.h"

#include "common.h"
#include "defaultlexer.h"
#include "defaultparser.h"
#include "compiler.h"
#include "virtualmachine.h"
#include "io.h"
#include "errorexception.h"
#include "breakexception.h"
#include "continueexception.h"
#include "node.h"
#include "runtimecontext.h"
#include "program.h"
#include "runtime.h"

list<string> Engine::args;

Engine::Action Engine::action;

string Engine::input;
string Engine::output;

Lexer *Engine::lexer;
Parser *Engine::parser;
Compiler *Engine::compiler;
VirtualMachine *Engine::virtualMachine;

bool Engine::error;

void Engine::init(int argc, char **argv) {
    defaults();

    for (int i = 0; i < argc; i++)
        args << argv[i];

    parseArgs();

    lexer = new DefaultLexer;
    parser = new DefaultParser;
    compiler = new Compiler;
    virtualMachine = new VirtualMachine;
}

void Engine::release() {
    delete lexer;
    delete parser;
    delete compiler;
    delete virtualMachine;
}

#include "time.h"
#include "utility.h"

void Engine::run() {
    if (error)
        return;

    try {
        switch (action) {
        case CompileAndRun: {
            Runtime::initializeCompiler(compiler);

            Node *ast = parser->parse(lexer->lex(IO::readFile(input)));
            Program *program = compiler->compile(ast);

            double t0 = clock();
            virtualMachine->run(program);
            double t1 = clock();
            IO::println("\nTime: " + Utility::toString((t1 - t0) / CLOCKS_PER_SEC) + "\n");

            delete ast;
            delete program;

            Runtime::release();

            break;
        }

        case Interpret: {
            Runtime::initializeInterpreter();

            Node *ast = parser->parse(lexer->lex(IO::readFile(input)));
            RuntimeContext *context = new RuntimeContext;

            double t0 = clock();
            IO::println("\n=> " + ast->eval(context).toString() + "\n");
            double t1 = clock();
            IO::println("\nTime: " + Utility::toString((t1 - t0) / CLOCKS_PER_SEC) + "\n");

            delete ast;
            delete context;

            Runtime::release();

            break;
        }
        }
    } catch (ErrorException *e) {
        IO::println(e->message());
        delete e;
    } catch (BreakException *e) {
        IO::println("runtime error: break not within a loop");
        delete e;
    } catch (ContinueException *e) {
        IO::println("runtime error: continue not within a loop");
        delete e;
    } catch (...) {
        IO::println("Whoops...");
    }
}

void Engine::defaults() {
    //action = None;
}

void Engine::parseArgs() {
    error = true;

    foreach (arg, args) {
        //if ((*arg)[0] == '-') {
        //    string option = arg->substr(1);

        //    if (option == "r")
        //        action = CompileAndRun;
        //    else if (option == "x")
        //        action = LoadAndRun;
        //    else if (option == "i")
        //        action = Interpret;
        //    else if (option == "c")
        //        action = Compile;
        //    else if (option == "d")
        //        action = Disassemble;
        //    else if (option == "o") {
        //        if (++arg == args.end()) {
        //            IO::error("output file name expected");
        //            return;
        //        }

        //        output = *arg;
        //    } else {
        //        IO::error("unknown option '" + option + "'");
        //        return;
        //    }
        //} else
        input = *arg;
    }

    //if (!input.empty() && output.empty()) {
    //    unsigned pos = input.rfind(".");
    //    output = pos == string::npos ? input : input.substr(0, pos);

    //    switch (action) {
    //    case Compile:
    //        output += ".vx";
    //        break;
    //    case Disassemble:
    //        output += ".va";
    //        break;
    //    default:
    //        break;
    //    }
    //}

    if (input.empty()) {
        //IO::error("input file is not specified");
        //return;

        input = "scripts/test.vi";
        action = CompileAndRun;
//        action = Interpret;
    }

    //if (action == None) {
    //    unsigned pos = input.rfind(".");
    //    string extension = pos == string::npos ? "" : input.substr(pos + 1, input.size());

    //    if (extension == "vi")
    //        action = CompileAndRun;
    //    else if (extension == "vx")
    //        action = LoadAndRun;
    //    else if (extension == "va")
    //        action = Disassemble;
    //    else {
    //        IO::error("action is not specified");
    //        return;
    //    }
    //}

    error = false;
}
