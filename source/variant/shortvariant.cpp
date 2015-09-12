#include "shortvariant.h"

#include "errorexception.h"
#include "utility.h"
#include "io.h"

ShortVariant::ShortVariant(short value)
    : value(value) {
}

void ShortVariant::dec() {
    value--;
}

void ShortVariant::inc() {
    value++;
}

void ShortVariant::scan() {
    IO::scan(value);
}

VariantPrivate *ShortVariant::clone() const {
    return new ShortVariant(value);
}

Variant::Type ShortVariant::type() const {
    return Variant::Short;
}

Variant ShortVariant::cast(Variant::Type type) const {
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

const void *ShortVariant::getValue() const {
    return &value;
}

int ShortVariant::size() const {
    return sizeof(value);
}

string ShortVariant::toString() const {
    return Utility::toString(value);
}

bool ShortVariant::toBool() const {
    return value;
}
