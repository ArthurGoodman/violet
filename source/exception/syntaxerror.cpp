#include "syntaxerror.h"

SyntaxError::SyntaxError(string message)
    : ErrorException(message) {
}

string SyntaxError::message() {
    return "syntax error: " + msg;
}

void SyntaxError::raise() {
    throw this;
}
