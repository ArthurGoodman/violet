#ifndef VARIANTPRIVATE_H
#define VARIANTPRIVATE_H

#include "variant.h"

class VariantPrivate {
public:
    virtual ~VariantPrivate();

    virtual Variant operation(Variant::Operation op, VariantPrivate *v) const;

    virtual void dec();
    virtual void inc();

    virtual void scan();

    virtual VariantPrivate *clone() const = 0;

    virtual Variant::Type type() const = 0;
    virtual Variant cast(Variant::Type type) const;
    virtual const void *getValue() const;
    virtual int size() const = 0;

    virtual string toString() const = 0;
    virtual bool toBool() const;

protected:
    void invalidOperationError() const;
    void invalidCastError(Variant::Type to) const;
};

#endif // VARIANTPRIVATE_H
