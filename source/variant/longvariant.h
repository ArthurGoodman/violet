#ifndef LONGVARIANT_H
#define LONGVARIANT_H

#include "variantprivate.h"

class LongVariant : public VariantPrivate {
    long long value;

public:
    LongVariant(long long value);

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

#endif // LONGVARIANT_H
