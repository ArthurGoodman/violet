#include "variantprivate.h"

#include "errorexception.h"

VariantPrivate::~VariantPrivate() {
}

Variant VariantPrivate::operation(Variant::Operation, VariantPrivate *) const {
    invalidOperationError();
    return Variant();
}

void VariantPrivate::dec() {
    invalidOperationError();
}

void VariantPrivate::inc() {
    invalidOperationError();
}

void VariantPrivate::scan() {
    invalidOperationError();
}

Variant VariantPrivate::cast(Variant::Type type) const {
    invalidCastError(type);
    return Variant();
}

const void *VariantPrivate::getValue() const {
    return 0;
}

bool VariantPrivate::toBool() const {
    invalidOperationError();
    return false;
}

void VariantPrivate::invalidOperationError() const {
    throw new ErrorException("invalid operation");
}

void VariantPrivate::invalidCastError(Variant::Type to) const {
    throw new ErrorException("invalid cast from '" + Variant(type()).toString() + "' to '" + Variant(to).toString() + "'");
}
