#ifndef INTVARIANT_H
#define INTVARIANT_H

#include "variantprivate.h"

class IntVariant : public VariantPrivate {
    int value;

public:
    IntVariant(int value);

    Variant operation(Variant::Operation op, VariantPrivate *v) const;

    void dec();
    void inc();

    void scan();

    VariantPrivate *clone() const;

    Variant::Type type() const;
    Variant cast(Variant::Type type) const;
    const void *getValue() const;
    int size() const;

    string toString() const;
    bool toBool() const;
};

#endif // INTVARIANT_H
