#include "compilationerror.h"

CompilationError::CompilationError(string message)
    : ErrorException(message) {
}

string CompilationError::message() {
    return "compilation error: " + msg;
}

void CompilationError::raise() {
    throw this;
}
