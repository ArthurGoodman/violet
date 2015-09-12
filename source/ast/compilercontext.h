#ifndef COMPILERCONTEXT_H
#define COMPILERCONTEXT_H

#include <map>
using namespace std;

#include "common.h"
#include "icontext.h"
#include "variant.h"

class Compiler;
class Node;

class CompilerContext : public IContext {
    struct VariableRecord {
        Variant type;
        byte index;
        bool isConst;

        VariableRecord();
        VariableRecord(Variant type, byte index, bool isConst);
    };

    Compiler *compiler;

    CompilerContext *parent;
    map<string, VariableRecord> locals;

public:
    CompilerContext(Compiler *compiler, CompilerContext *parent = 0);

    IContext *childContext();

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
    bool setLocal(string name, const Variant &type);

    void gen(byte op);

    void push(const Variant &value);
    void pop(const Variant &value);
    void load(string name);
    void store(string name);

    Variant::Type coerce(const Variant &lt, const Variant &rt);

    void toBool(const Variant &lt, const Variant &rt);
};

#endif // COMPILERCONTEXT_H
