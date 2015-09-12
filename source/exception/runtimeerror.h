#ifndef RUNTIMEERROR_H
#define RUNTIMEERROR_H

#include "errorexception.h"

class RuntimeError : public ErrorException {
public:
    RuntimeError(string message);

    string message();

    void raise();
};

#endif // RUNTIMEERROR_H
