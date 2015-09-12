#ifndef EXCEPTION_H
#define EXCEPTION_H

class Exception {
public:
    virtual ~Exception();

    virtual void raise() = 0;
};

#endif // EXCEPTION_H
