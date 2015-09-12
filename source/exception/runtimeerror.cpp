#include "runtimeerror.h"

RuntimeError::RuntimeError(string message)
    : ErrorException(message) {
}

string RuntimeError::message() {
    return "runtime error: " + msg;
}

void RuntimeError::raise() {
    throw this;
}
