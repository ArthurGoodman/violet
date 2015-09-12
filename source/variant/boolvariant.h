#ifndef BOOLVARIANT_H
#define BOOLVARIANT_H

#include "variantprivate.h"

class BoolVariant : public VariantPrivate {
    bool value;

public:
    BoolVariant(bool value);

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

#endif // BOOLVARIANT_H
