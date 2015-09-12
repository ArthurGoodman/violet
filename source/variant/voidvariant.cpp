#include "voidvariant.h"

#include "errorexception.h"

void VoidVariant::dec() {
    invalidOperationError();
}

void VoidVariant::inc() {
    invalidOperationError();
}

void VoidVariant::scan() {
    invalidOperationError();
}

VariantPrivate *VoidVariant::clone() const {
    return new VoidVariant;
}

Variant::Type VoidVariant::type() const {
    return Variant::Void;
}

int VoidVariant::size() const {
    return 0;
}

string VoidVariant::toString() const {
    return "void";
}

bool VoidVariant::toBool() const {
    return false;
}
