#ifndef BREAKEXCEPTION_H
#define BREAKEXCEPTION_H

#include "exception.h"

class BreakException : public Exception {
public:
    void raise();
};

#endif // BREAKEXCEPTION_H
