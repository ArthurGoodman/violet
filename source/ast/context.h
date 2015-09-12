#ifndef CONTEXT_H
#define CONTEXT_H

#include "variant.h"

class Node;

class Context {
public:
    virtual ~Context();

    virtual Context *childContext() = 0;

    virtual bool hasLocal(string name) = 0;

    virtual Variant get(string name) = 0;

    virtual bool set(string name, const Variant &value) = 0;
    virtual void defineLocal(string name, const Variant &value, bool isConst = false) = 0;

    virtual Variant cast(const Variant &value, Variant::Type type) = 0;

    virtual Variant constant(const Variant &value) = 0;

    virtual Variant operation(Variant::Operation op, const Variant &lv, const Variant &rv) = 0;
    virtual Variant logicAnd(const Variant &lv, const Variant &rv) = 0;
    virtual Variant logicOr(const Variant &lv, const Variant &rv) = 0;
    virtual Variant logicNot(const Variant &v) = 0;

    virtual void dec(string name) = 0;
    virtual void inc(string name) = 0;

    virtual void scan(string name) = 0;
    virtual void print(const Variant &v) = 0;

    virtual Variant size(const Variant &v) = 0;

    virtual void If(Node *condition, Node *body, Node *elseBody) = 0;
    virtual void While(Node *condition, Node *body) = 0;
    virtual void Do(Node *body, Node *condition) = 0;
    virtual void For(Node *preffix, Node *condition, Node *suffix, Node *body) = 0;

    virtual Variant getVoid() = 0;
    virtual void empty() = 0;
    virtual void ignore(const Variant &v) = 0;

    virtual void error(string message) = 0;
};

#endif // CONTEXT_H
