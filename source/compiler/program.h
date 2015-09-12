#ifndef PROGRAM_H
#define PROGRAM_H

#include "common.h"
#include "variant.h"
#include "vector.h"

class Program {
    Vector code;
    Vector constants;

    int localsSize;

public:
    Program(Vector code, Vector constants, int localsSize);

    const Vector &getCode();
    const Vector &getConstants();

    int getLocalsSize();
};

#endif // PROGRAM_H
