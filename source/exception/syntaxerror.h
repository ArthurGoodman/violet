#ifndef SYNTAXERROR_H
#define SYNTAXERROR_H

#include "errorexception.h"

class SyntaxError : public ErrorException {
public:
    SyntaxError(string message);

    string message();

    void raise();
};

#endif // SYNTAXERROR_H
