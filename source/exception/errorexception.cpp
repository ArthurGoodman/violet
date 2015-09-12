#include "errorexception.h"

ErrorException::ErrorException(string message)
    : msg(message) {
}

string ErrorException::message() {
    return "error: " + msg;
}

void ErrorException::raise() {
    throw this;
}
