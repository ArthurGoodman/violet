#ifndef TYPEVARIANT_H
#define TYPEVARIANT_H

#include "variantprivate.h"

class TypeVariant : public VariantPrivate {
    Variant::Type value;

public:
    TypeVariant(Variant::Type value);

    VariantPrivate *clone() const;

    Variant::Type type() const;
    Variant cast(Variant::Type type) const;
    int size() const;

    string toString() const;
};

#endif // TYPEVARIANT_H
