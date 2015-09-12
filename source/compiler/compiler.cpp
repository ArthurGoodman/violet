#include "compiler.h"

#include "compilercontext.h"
#include "node.h"
#include "program.h"
#include "instructions.h"

Compiler::Frame::Frame()
    : localPointer(0) {
}

Program *Compiler::compile(Node *ast) {
    CompilerContext *context = new CompilerContext(this);

    code.clear();
    constants.clear();

    pushFrame();

    ast->eval(context);

    delete context;

    return new Program(code, constants, frames.top().localPointer);
}

void Compiler::gen(byte op) {
    code << op;
}

int Compiler::offset() {
    return code.size();
}

void Compiler::set(int offset, byte op) {
    code[offset] = op;
}

int Compiler::local(int size) {
    int temp = frames.top().localPointer;
    frames.top().localPointer += size;
    return temp;
}

short Compiler::constant(Variant value) {
    constants.resize(constants.size() + value.size());
    memcpy(constants.data() + constants.size() - value.size(), value.getValue(), value.size());
    return constants.size() - value.size();
}

void Compiler::pushFrame() {
    frames.push(Frame());
}

void Compiler::popFrame() {
    frames.pop();
}
