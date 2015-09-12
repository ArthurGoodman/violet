#include "doublevariant.h"

#include "errorexception.h"
#include "utility.h"
#include "io.h"

DoubleVariant::DoubleVariant(double value)
    : value(value) {
}

Variant DoubleVariant::operation(Variant::Operation op, VariantPrivate *v) const {
    switch (op) {
    case Variant::Add:
        return value + *(double *)v->getValue();
    case Variant::Sub:
        return value - *(double *)v->getValue();
    case Variant::Mul:
        return value * *(double *)v->getValue();
    case Variant::Div:
        return value / *(double *)v->getValue();
    case Variant::Mod:
        return fmod(value, *(double *)v->getValue());

    case Variant::Lt:
        return value < *(double *)v->getValue();
    case Variant::Gt:
        return value > *(double *)v->getValue();
    case Variant::Le:
        return value <= *(double *)v->getValue();
    case Variant::Ge:
        return value >= *(double *)v->getValue();
    case Variant::Eq:
        return value == *(double *)v->getValue();
    case Variant::Ne:
        return value != *(double *)v->getValue();

    default:
        invalidOperationError();
        return Variant();
    }
}

void DoubleVariant::dec() {
    value--;
}

void DoubleVariant::inc() {
    value++;
}

void DoubleVariant::scan() {
    IO::scan(value);
}

VariantPrivate *DoubleVariant::clone() const {
    return new DoubleVariant(value);
}

Variant::Type DoubleVariant::type() const {
    return Variant::Double;
}

Variant DoubleVariant::cast(Variant::Type type) const {
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

const void *DoubleVariant::getValue() const {
    return &value;
}

int DoubleVariant::size() const {
    return sizeof(value);
}

string DoubleVariant::toString() const {
    return Utility::toString(value);
}

bool DoubleVariant::toBool() const {
    return value;
}
