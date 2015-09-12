#include "runtimecontext.h"

#include "runtimeerror.h"
#include "io.h"
#include "node.h"
#include "breakexception.h"
#include "continueexception.h"

RuntimeContext::VariableRecord::VariableRecord() {
}

RuntimeContext::VariableRecord::VariableRecord(const Variant &value, bool isConst)
    : value(value), isConst(isConst) {
}

RuntimeContext::RuntimeContext(RuntimeContext *parent)
    : parent(parent) {
}

Context *RuntimeContext::childContext() {
    return new RuntimeContext(this);
}

bool RuntimeContext::hasLocal(string name) {
    return locals.find(name) != locals.end();
}

Variant RuntimeContext::get(string name) {
    if (hasLocal(name))
        return getLocal(name);
    else if (parent)
        return parent->get(name);

    throw new RuntimeError("undefined variable '" + name + "'");
}

bool RuntimeContext::set(string name, const Variant &value) {
    if (setLocal(name, value))
        return true;
    else if (parent)
        return parent->set(name, value);

    return false;
}

void RuntimeContext::defineLocal(string name, const Variant &value, bool isConst) {
    locals[name] = VariableRecord(value, isConst);
}

Variant RuntimeContext::cast(const Variant &value, Variant::Type type) {
    return value.cast(type);
}

Variant RuntimeContext::constant(const Variant &value) {
    return value;
}

Variant RuntimeContext::operation(Variant::Operation op, const Variant &lv, const Variant &rv) {
    return lv.operation(op, rv);
}

Variant RuntimeContext::logicAnd(const Variant &lv, const Variant &rv) {
    return lv.toBool() && rv.toBool();
}

Variant RuntimeContext::logicOr(const Variant &lv, const Variant &rv) {
    return lv.toBool() || rv.toBool();
}

Variant RuntimeContext::logicNot(const Variant &v) {
    return !v.toBool();
}

void RuntimeContext::dec(string name) {
    if (hasLocal(name))
        locals.at(name).value.dec();
    else if (parent)
        parent->dec(name);
}

void RuntimeContext::inc(string name) {
    if (hasLocal(name))
        locals.at(name).value.inc();
    else if (parent)
        parent->inc(name);
}

void RuntimeContext::scan(string name) {
    if (hasLocal(name)) {
        locals.at(name).value.scan();
        return;
    } else if (parent)
        parent->scan(name);
}

void RuntimeContext::print(const Variant &v) {
    IO::print(v.toString());
}

Variant RuntimeContext::size(const Variant &v) {
    return v.size();
}

void RuntimeContext::If(Node *condition, Node *body, Node *elseBody) {
    if (condition->eval(this).toBool())
        body->eval(this);
    else if (elseBody)
        elseBody->eval(this);
}

void RuntimeContext::While(Node *condition, Node *body) {
    while (condition->eval(this).toBool())
        try {
            body->eval(this);
        } catch (BreakException *e) {
            delete e;
            break;
        } catch (ContinueException *e) {
            delete e;
            continue;
        } catch (Exception *e) {
            e->raise();
        }
}

void RuntimeContext::Do(Node *body, Node *condition) {
    do
        try {
            body->eval(this);
        } catch (BreakException *e) {
            delete e;
            break;
        } catch (ContinueException *e) {
            delete e;
            continue;
        } catch (Exception *e) {
            e->raise();
        }
    while (condition->eval(this).toBool());
}

void RuntimeContext::For(Node *preffix, Node *condition, Node *suffix, Node *body) {
    preffix->eval(this);

    while (condition->eval(this).toBool()) {
        try {
            body->eval(this);
            suffix->eval(this);
        } catch (BreakException *e) {
            delete e;
            break;
        } catch (ContinueException *e) {
            suffix->eval(this);
            delete e;
            continue;
        } catch (Exception *e) {
            e->raise();
        }
    }
}

Variant RuntimeContext::getVoid() {
    return Variant();
}

void RuntimeContext::empty() {
}

void RuntimeContext::ignore(const Variant &) {
}

void RuntimeContext::error(string message) {
    throw new RuntimeError(message);
}

Variant RuntimeContext::getLocal(string name) {
    return locals.at(name).value;
}

bool RuntimeContext::setLocal(string name, const Variant &value) {
    if (hasLocal(name)) {
        if (locals.at(name).isConst)
            throw new RuntimeError("assignment of read-only variable '" + name + "'");

        locals.at(name).value = value.cast(locals.at(name).value.type());

        return true;
    }

    return false;
}
