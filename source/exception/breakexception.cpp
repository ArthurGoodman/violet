#include "breakexception.h"

void BreakException::raise() {
    throw this;
}
