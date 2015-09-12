#include "program.h"

Program::Program(Vector code, Vector constants, int localsSize)
    : code(code), constants(constants), localsSize(localsSize) {
}

const Vector &Program::getCode() {
    return code;
}

const Vector &Program::getConstants() {
    return constants;
}

int Program::getLocalsSize() {
    return localsSize;
}
