#include "charvariant.h"

#include "errorexception.h"
#include "utility.h"
#include "io.h"

CharVariant::CharVariant(char value)
    : value(value) {
}

void CharVariant::dec() {
    value--;
}

void CharVariant::inc() {
    value++;
}

void CharVariant::scan() {
    IO::scan(value);
}

VariantPrivate *CharVariant::clone() const {
    return new CharVariant(value);
}

Variant::Type CharVariant::type() const {
    return Variant::Char;
}

Variant CharVariant::cast(Variant::Type type) const {
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

const void *CharVariant::getValue() const {
    return &value;
}

int CharVariant::size() const {
    return sizeof(value);
}

string CharVariant::toString() const {
    return Utility::toString(value);
}

bool CharVariant::toBool() const {
    return value;
}
