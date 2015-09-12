#ifndef DOUBLEVARIANT_H
#define DOUBLEVARIANT_H

#include "variantprivate.h"

class DoubleVariant : public VariantPrivate {
    double value;

public:
    DoubleVariant(double value);

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

#endif // DOUBLEVARIANT_H
