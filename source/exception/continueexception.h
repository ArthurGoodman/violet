#ifndef CONTINUEEXCEPTION_H
#define CONTINUEEXCEPTION_H

#include "exception.h"

class ContinueException : public Exception {
public:
    void raise();
};

#endif // CONTINUEEXCEPTION_H
