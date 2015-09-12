#ifndef COMPILATIONERROR_H
#define COMPILATIONERROR_H

#include "errorexception.h"

class CompilationError : public ErrorException {
public:
    CompilationError(string message);

    string message();

    void raise();
};

#endif // COMPILATIONERROR_H
