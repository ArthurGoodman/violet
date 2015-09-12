#include "variant.h"

#include "voidvariant.h"
#include "boolvariant.h"
#include "charvariant.h"
#include "shortvariant.h"
#include "intvariant.h"
#include "longvariant.h"
#include "floatvariant.h"
#include "doublevariant.h"
#include "typevariant.h"

Variant::Variant()
    : data(new VoidVariant) {
}

Variant::Variant(bool value)
    : data(new BoolVariant(value)) {
}

Variant::Variant(char value)
    : data(new CharVariant(value)) {
}

Variant::Variant(short value)
    : data(new ShortVariant(value)) {
}

Variant::Variant(int value)
    : data(new IntVariant(value)) {
}

Variant::Variant(long long value)
    : data(new LongVariant(value)) {
}

Variant::Variant(float value)
    : data(new FloatVariant(value)) {
}

Variant::Variant(double value)
    : data(new DoubleVariant(value)) {
}

Variant::Variant(Variant::Type value)
    : data(new TypeVariant(value)) {
}

Variant::Variant(const Variant &v)
    : data(v.data->clone()) {
}

Variant::~Variant() {
    delete data;
}

Variant &Variant::operator=(const Variant &v) {
    delete data;
    data = v.data->clone();
    return *this;
}

Variant Variant::operation(Variant::Operation op, const Variant &v) const {
    Type t = coerce(type(), v.type());
    return cast(t).data->operation(op, v.cast(t).data);
}

void Variant::dec() {
    data->dec();
}

void Variant::inc() {
    data->inc();
}

void Variant::scan() {
    data->scan();
}

Variant::Type Variant::type() const {
    return data->type();
}

Variant Variant::cast(Type type) const {
    return data->cast(type);
}

const void *Variant::getValue() const {
    return data->getValue();
}

int Variant::size() const {
    return data->size();
}

string Variant::toString() const {
    return data->toString();
}

bool Variant::toBool() const {
    return data->toBool();
}

Variant::Type Variant::coerce(Variant::Type a, Variant::Type b) {
    return a <= Int && b <= Int ? Int : max(a, b);
}

int Variant::typeSize(Variant::Type type) {
    switch (type) {
    case Variant::Bool:
        return sizeof(bool);
    case Variant::Char:
        return sizeof(char);
    case Variant::Short:
        return sizeof(short);
    case Variant::Int:
        return sizeof(int);
    case Variant::Long:
        return sizeof(long long);
    case Variant::Float:
        return sizeof(float);
    case Variant::Double:
        return sizeof(double);
    default:
        return 0;
    }
}
