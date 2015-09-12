#include "typevariant.h"

TypeVariant::TypeVariant(Variant::Type value)
    : value(value) {
}

VariantPrivate *TypeVariant::clone() const {
    return new TypeVariant(value);
}

Variant::Type TypeVariant::type() const {
    return value;
}

Variant TypeVariant::cast(Variant::Type type) const {
    switch (value) {
    case Variant::Bool:
    case Variant::Char:
    case Variant::Short:
    case Variant::Int:
    case Variant::Long:
    case Variant::Float:
    case Variant::Double:
        switch (type) {
        case Variant::Bool:
        case Variant::Char:
        case Variant::Short:
        case Variant::Int:
        case Variant::Long:
        case Variant::Float:
        case Variant::Double:
            return type;

        default:
            invalidCastError(type);
            return Variant::Undefined;
        }

    default:
        invalidCastError(type);
        return Variant::Undefined;
    }
}

int TypeVariant::size() const {
    return Variant::typeSize(value);
}

string TypeVariant::toString() const {
    switch (value) {
    case Variant::Void:
        return "void";

    case Variant::Bool:
        return "bool";

    case Variant::Char:
        return "char";

    case Variant::Short:
        return "short";

    case Variant::Int:
        return "int";

    case Variant::Long:
        return "long";

    case Variant::Float:
        return "float";

    case Variant::Double:
        return "double";

    default:
        return "";
    }
}
