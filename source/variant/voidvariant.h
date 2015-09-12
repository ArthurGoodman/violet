#ifndef VOIDVARIANT_H
#define VOIDVARIANT_H

#include "variantprivate.h"

class VoidVariant : public VariantPrivate {
public:
    void dec();
    void inc();

    void scan();

    VariantPrivate *clone() const;

    Variant::Type type() const;
    int size() const;

    string toString() const;
    bool toBool() const;
};

#endif // VOIDVARIANT_H
