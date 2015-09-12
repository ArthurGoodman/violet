#include "boolvariant.h"

#include "errorexception.h"
#include "utility.h"
#include "io.h"

BoolVariant::BoolVariant(bool value)
    : value(value) {
}

void BoolVariant::dec() {
    invalidOperationError();
}

void BoolVariant::inc() {
    invalidOperationError();
}

void BoolVariant::scan() {
    IO::scan(value);
}

VariantPrivate *BoolVariant::clone() const {
    return new BoolVariant(value);
}

Variant::Type BoolVariant::type() const {
    return Variant::Bool;
}

Variant BoolVariant::cast(Variant::Type type) const {
    switch (type) {
    case Variant::Bool:
        return Variant((bool)value);

    case Variant::Char:
        return Variant((char)value);

    case Variant::Short:
        return Variant((short)value);

    case Variant::Int:
        return Variant((int)value);

    case Variant::Long:
        return Variant((long long)value);

    case Variant::Float:
        return Variant((float)value);

    case Variant::Double:
        return Variant((double)value);

    default:
        invalidCastError(type);
        return Variant();
    }
}

const void *BoolVariant::getValue() const {
    return &value;
}

int BoolVariant::size() const {
    return sizeof(value);
}

string BoolVariant::toString() const {
    return value ? "true" : "false";
}

bool BoolVariant::toBool() const {
    return value;
}
