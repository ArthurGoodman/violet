#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

#include <vector>
#include <string>
using namespace std;

#include "vector.h"
#include "variant.h"

class Program;

class VirtualMachine {
    static vector<string> instructions;

    int offset;

    Program *p;

    Vector stack;
    Vector locals;

public:
    void run(Program *p);

private:
    byte *constant();
    byte *local();

    void printProgram(string fileName, Program *p);

    template <typename T>
    void push(const T &value);

    template <typename T>
    T pop();

    void pushVariant(const Variant &value);
    Variant popVariant(Variant::Type type);
};

template <typename T>
void VirtualMachine::push(const T &value) {
    *(T *)stack.allocate(sizeof(T)) = value;
}

template <typename T>
T VirtualMachine::pop() {
    T value = *(T *)(stack.data() + stack.size() - sizeof(T));
    stack.free(sizeof(T));
    return value;
}

#endif // VIRTUALMACHINE_H
