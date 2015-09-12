#ifndef ERROREXCEPTION_H
#define ERROREXCEPTION_H

#include <string>
using namespace std;

#include "exception.h"

class ErrorException : public Exception {
protected:
    string msg;

public:
    ErrorException(string message);

    virtual string message();

    virtual void raise();
};

#endif // ERROREXCEPTION_H
