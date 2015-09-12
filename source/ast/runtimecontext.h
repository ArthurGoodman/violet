#ifndef RUNTIMECONTEXT_H
#define RUNTIMECONTEXT_H

#include <map>
using namespace std;

#include "context.h"
#include "variant.h"

class Node;

class RuntimeContext : public Context {
    struct VariableRecord {
        Variant value;
        bool isConst;

        VariableRecord();
        VariableRecord(const Variant &value, bool isConst);
    };

    RuntimeContext *parent;
    map<string, VariableRecord> locals;

public:
    RuntimeContext(RuntimeContext *parent = 0);

    Context *childContext();

    bool hasLocal(string name);

    Variant get(string name);

    bool set(string name, const Variant &value);
    void defineLocal(string name, const Variant &value, bool isConst = false);

    Variant cast(const Variant &value, Variant::Type type);

    Variant constant(const Variant &value);

    Variant operation(Variant::Operation op, const Variant &lv, const Variant &rv);
    Variant logicAnd(const Variant &lv, const Variant &rv);
    Variant logicOr(const Variant &lv, const Variant &rv);
    Variant logicNot(const Variant &v);

    void dec(string name);
    void inc(string name);

    void scan(string name);
    void print(const Variant &v);

    Variant size(const Variant &v);

    void If(Node *condition, Node *body, Node *elseBody);
    void While(Node *condition, Node *body);
    void Do(Node *body, Node *condition);
    void For(Node *preffix, Node *condition, Node *suffix, Node *body);

    Variant getVoid();
    void empty();
    void ignore(const Variant &v);

    void error(string message);

private:
    Variant getLocal(string name);
    bool setLocal(string name, const Variant &value);
};

#endif // RUNTIMECONTEXT_H
