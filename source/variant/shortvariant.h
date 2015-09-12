#ifndef SHORTVARIANT_H
#define SHORTVARIANT_H

#include "variantprivate.h"

class ShortVariant : public VariantPrivate {
    short value;

public:
    ShortVariant(short value);

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

#endif // SHORTVARIANT_H
