#ifndef LEXICALERROR_H
#define LEXICALERROR_H

#include "errorexception.h"

class LexicalError : public ErrorException {
public:
    LexicalError(string message);

    string message();

    void raise();
};

#endif // LEXICALERROR_H
