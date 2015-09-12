#include "longvariant.h"

#include "errorexception.h"
#include "utility.h"
#include "io.h"

LongVariant::LongVariant(long long value)
    : value(value) {
}

Variant LongVariant::operation(Variant::Operation op, VariantPrivate *v) const {
    switch (op) {
    case Variant::Add:
        return value + *(long long *)v->getValue();
    case Variant::Sub:
        return value - *(long long *)v->getValue();
    case Variant::Mul:
        return value * *(long long *)v->getValue();
    case Variant::Div:
        if (!*(long long *)v->getValue())
            throw new ErrorException("division by zero");
        return value / *(long long *)v->getValue();
    case Variant::Mod:
        if (!*(long long *)v->getValue())
            throw new ErrorException("division by zero");
        return value % *(long long *)v->getValue();

    case Variant::Lt:
        return value < *(long long *)v->getValue();
    case Variant::Gt:
        return value > *(long long *)v->getValue();
    case Variant::Le:
        return value <= *(long long *)v->getValue();
    case Variant::Ge:
        return value >= *(long long *)v->getValue();
    case Variant::Eq:
        return value == *(long long *)v->getValue();
    case Variant::Ne:
        return value != *(long long *)v->getValue();

    default:
        invalidOperationError();
        return Variant();
    }
}

void LongVariant::dec() {
    value--;
}

void LongVariant::inc() {
    value++;
}

void LongVariant::scan() {
    IO::scan(value);
}

VariantPrivate *LongVariant::clone() const {
    return new LongVariant(value);
}

Variant::Type LongVariant::type() const {
    return Variant::Long;
}

Variant LongVariant::cast(Variant::Type type) const {
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

const void *LongVariant::getValue() const {
    return &value;
}

int LongVariant::size() const {
    return sizeof(value);
}

string LongVariant::toString() const {
    return Utility::toString(value);
}

bool LongVariant::toBool() const {
    return value;
}
