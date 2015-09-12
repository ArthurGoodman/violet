#ifndef FLOATVARIANT_H
#define FLOATVARIANT_H

#include "variantprivate.h"

class FloatVariant : public VariantPrivate {
    float value;

public:
    FloatVariant(float value);

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

#endif // FLOATVARIANT_H
