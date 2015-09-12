#include "lexicalerror.h"

LexicalError::LexicalError(string message)
    : ErrorException(message) {
}

string LexicalError::message() {
    return "lexical error: " + msg;
}

void LexicalError::raise() {
    throw this;
}
