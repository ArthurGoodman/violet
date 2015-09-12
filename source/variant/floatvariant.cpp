#include "floatvariant.h"

#include "errorexception.h"
#include "utility.h"
#include "io.h"

FloatVariant::FloatVariant(float value)
    : value(value) {
}

Variant FloatVariant::operation(Variant::Operation op, VariantPrivate *v) const {
    switch (op) {
    case Variant::Add:
        return value + *(float *)v->getValue();
    case Variant::Sub:
        return value - *(float *)v->getValue();
    case Variant::Mul:
        return value * *(float *)v->getValue();
    case Variant::Div:
        return value / *(float *)v->getValue();
    case Variant::Mod:
        return fmodf(value, *(float *)v->getValue());

    case Variant::Lt:
        return value < *(float *)v->getValue();
    case Variant::Gt:
        return value > *(float *)v->getValue();
    case Variant::Le:
        return value <= *(float *)v->getValue();
    case Variant::Ge:
        return value >= *(float *)v->getValue();
    case Variant::Eq:
        return value == *(float *)v->getValue();
    case Variant::Ne:
        return value != *(float *)v->getValue();

    default:
        invalidOperationError();
        return Variant();
    }
}

void FloatVariant::dec() {
    value--;
}

void FloatVariant::inc() {
    value++;
}

void FloatVariant::scan() {
    IO::scan(value);
}

VariantPrivate *FloatVariant::clone() const {
    return new FloatVariant(value);
}

Variant::Type FloatVariant::type() const {
    return Variant::Float;
}

Variant FloatVariant::cast(Variant::Type type) const {
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

const void *FloatVariant::getValue() const {
    return &value;
}

int FloatVariant::size() const {
    return sizeof(value);
}

string FloatVariant::toString() const {
    return Utility::toString(value);
}

bool FloatVariant::toBool() const {
    return value;
}
