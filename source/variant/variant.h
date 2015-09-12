#ifndef VARIANT_H
#define VARIANT_H

#include <string>
using namespace std;

class VariantPrivate;

class Variant {
    VariantPrivate *data;

public:
    enum Type {
        Undefined = -1,

        Void,

        Bool,
        Char,
        Short,
        Int,
        Long,
        Float,
        Double
    };

    enum Operation {
        Add,
        Sub,
        Mul,
        Div,
        Mod,

        Lt,
        Gt,
        Le,
        Ge,
        Eq,
        Ne,
    };

public:
    Variant();
    Variant(bool value);
    Variant(char value);
    Variant(short value);
    Variant(int value);
    Variant(long long value);
    Variant(float value);
    Variant(double value);
    Variant(Type value);

    Variant(const Variant &v);

    ~Variant();

    Variant &operator=(const Variant &v);

    Variant operation(Operation op, const Variant &v) const;

    void dec();
    void inc();

    void scan();

    Type type() const;
    Variant cast(Type type) const;
    const void *getValue() const;
    int size() const;

    string toString() const;
    bool toBool() const;

    static Type coerce(Type a, Type b);
    static int typeSize(Type type);
};

#endif // VARIANT_H
