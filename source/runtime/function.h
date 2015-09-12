#ifndef FUNCTION_H
#define FUNCTION_H

#include <list>
using namespace std;

class Variant;

class Function {
public:
    virtual ~Function();

    virtual Variant call(list<Variant> args) = 0;
};

#endif // FUNCTION_H
