#ifndef COMPILER_H
#define COMPILER_H

#include <stack>
using namespace std;

#include "common.h"
#include "variant.h"

class Program;
class Node;

class Compiler {
    struct Frame {
        int localPointer;

        Frame();
    };

    vector<byte> code;
    vector<byte> constants;

    stack<Frame> frames;

public:
    Program *compile(Node *ast);

    void gen(byte op);

    int offset();
    void set(int offset, byte op);

    int local(int size);
    short constant(Variant value);

    void pushFrame();
    void popFrame();
};

#endif // COMPILER_H
