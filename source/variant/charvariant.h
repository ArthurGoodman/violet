#ifndef CHARVARIANT_H
#define CHARVARIANT_H

#include "variantprivate.h"

class CharVariant : public VariantPrivate {
    char value;

public:
    CharVariant(char value);

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

#endif // CHARVARIANT_H
