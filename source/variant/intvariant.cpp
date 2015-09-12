#include "intvariant.h"

#include "errorexception.h"
#include "utility.h"
#include "io.h"

IntVariant::IntVariant(int value)
    : value(value) {
}

Variant IntVariant::operation(Variant::Operation op, VariantPrivate *v) const {
    switch (op) {
    case Variant::Add:
        return value + *(int *)v->getValue();
    case Variant::Sub:
        return value - *(int *)v->getValue();
    case Variant::Mul:
        return value * *(int *)v->getValue();
    case Variant::Div:
        if (!*(int *)v->getValue())
            throw new ErrorException("division by zero");
        return value / *(int *)v->getValue();
    case Variant::Mod:
        if (!*(int *)v->getValue())
            throw new ErrorException("division by zero");
        return value % *(int *)v->getValue();

    case Variant::Lt:
        return value < *(int *)v->getValue();
    case Variant::Gt:
        return value > *(int *)v->getValue();
    case Variant::Le:
        return value <= *(int *)v->getValue();
    case Variant::Ge:
        return value >= *(int *)v->getValue();
    case Variant::Eq:
        return value == *(int *)v->getValue();
    case Variant::Ne:
        return value != *(int *)v->getValue();

    default:
        invalidOperationError();
        return Variant();
    }
}

void IntVariant::dec() {
    value--;
}

void IntVariant::inc() {
    value++;
}

void IntVariant::scan() {
    IO::scan(value);
}

VariantPrivate *IntVariant::clone() const {
    return new IntVariant(value);
}

Variant::Type IntVariant::type() const {
    return Variant::Int;
}

Variant IntVariant::cast(Variant::Type type) const {
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

const void *IntVariant::getValue() const {
    return &value;
}

int IntVariant::size() const {
    return sizeof(value);
}

string IntVariant::toString() const {
    return Utility::toString(value);
}

bool IntVariant::toBool() const {
    return value;
}
