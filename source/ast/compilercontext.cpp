#include "compilercontext.h"

#include "compiler.h"
#include "compilationerror.h"
#include "instructions.h"
#include "node.h"

CompilerContext::VariableRecord::VariableRecord() {
}

CompilerContext::VariableRecord::VariableRecord(Variant type, byte index, bool isConst)
    : type(type), index(index), isConst(isConst) {
}

CompilerContext::CompilerContext(Compiler *compiler, CompilerContext *parent)
    : compiler(compiler), parent(parent) {
}

IContext *CompilerContext::childContext() {
    return new CompilerContext(compiler, this);
}

bool CompilerContext::hasLocal(string name) {
    return locals.find(name) != locals.end();
}

Variant CompilerContext::get(string name) {
    if (hasLocal(name))
        return getLocal(name);
    else if (parent)
        return parent->get(name);

    throw new CompilationError("undefined variable '" + name + "'");
}

bool CompilerContext::set(string name, const Variant &type) {
    if (setLocal(name, type))
        return true;
    else if (parent)
        return parent->set(name, type);

    return false;
}

void CompilerContext::defineLocal(string name, const Variant &type, bool isConst) {
    locals[name] = VariableRecord(type, compiler->local(type.size()), isConst);
    store(name);
}

Variant CompilerContext::cast(const Variant &value, Variant::Type type) {
    if (value.type() != type) {
        gen(iCast);
        gen((byte)value.type() << 4 | (byte)type);
    }

    return value.cast(type);
}

Variant CompilerContext::constant(const Variant &value) {
    push(value);
    return value.type();
}

Variant CompilerContext::operation(Variant::Operation op, const Variant &lt, const Variant &rt) {
    Variant::Type type = coerce(lt, rt);

    switch (op) {
    case Variant::Add:
        switch (type) {
        case Variant::Int:
            gen(iIAdd);
            break;
        case Variant::Long:
            gen(iLAdd);
            break;
        case Variant::Float:
            gen(iFAdd);
            break;
        case Variant::Double:
            gen(iDAdd);
            break;

        default:
            break;
        }

        return type;

    case Variant::Sub:
        switch (type) {
        case Variant::Int:
            gen(iISub);
            break;
        case Variant::Long:
            gen(iLSub);
            break;
        case Variant::Float:
            gen(iFSub);
            break;
        case Variant::Double:
            gen(iDSub);
            break;

        default:
            break;
        }

        return type;

    case Variant::Mul:
        switch (type) {
        case Variant::Int:
            gen(iIMul);
            break;
        case Variant::Long:
            gen(iLMul);
            break;
        case Variant::Float:
            gen(iFMul);
            break;
        case Variant::Double:
            gen(iDMul);
            break;

        default:
            break;
        }

        return type;

    case Variant::Div:
        switch (type) {
        case Variant::Int:
            gen(iIDiv);
            break;
        case Variant::Long:
            gen(iLDiv);
            break;
        case Variant::Float:
            gen(iFDiv);
            break;
        case Variant::Double:
            gen(iDDiv);
            break;

        default:
            break;
        }

        return type;

    case Variant::Mod:
        switch (type) {
        case Variant::Int:
            gen(iIMod);
            break;
        case Variant::Long:
            gen(iLMod);
            break;
        case Variant::Float:
            gen(iFMod);
            break;
        case Variant::Double:
            gen(iDMod);
            break;

        default:
            break;
        }

        return type;

    case Variant::Lt:
        switch (type) {
        case Variant::Int:
            gen(iICmp);
            break;
        case Variant::Long:
            gen(iLCmp);
            break;
        case Variant::Float:
            gen(iFCmp);
            break;
        case Variant::Double:
            gen(iDCmp);
            break;

        default:
            break;
        }

        gen(iLt);

        return Variant::Bool;

    case Variant::Gt:
        switch (type) {
        case Variant::Int:
            gen(iICmp);
            break;
        case Variant::Long:
            gen(iLCmp);
            break;
        case Variant::Float:
            gen(iFCmp);
            break;
        case Variant::Double:
            gen(iDCmp);
            break;

        default:
            break;
        }

        gen(iGt);

        return Variant::Bool;

    case Variant::Le:
        switch (type) {
        case Variant::Int:
            gen(iICmp);
            break;
        case Variant::Long:
            gen(iLCmp);
            break;
        case Variant::Float:
            gen(iFCmp);
            break;
        case Variant::Double:
            gen(iDCmp);
            break;

        default:
            break;
        }

        gen(iLe);

        return Variant::Bool;

    case Variant::Ge:
        switch (type) {
        case Variant::Int:
            gen(iICmp);
            break;
        case Variant::Long:
            gen(iLCmp);
            break;
        case Variant::Float:
            gen(iFCmp);
            break;
        case Variant::Double:
            gen(iDCmp);
            break;

        default:
            break;
        }

        gen(iGe);

        return Variant::Bool;

    case Variant::Eq:
        switch (type) {
        case Variant::Int:
            gen(iICmp);
            break;
        case Variant::Long:
            gen(iLCmp);
            break;
        case Variant::Float:
            gen(iFCmp);
            break;
        case Variant::Double:
            gen(iDCmp);
            break;

        default:
            break;
        }

        gen(iEq);

        return Variant::Bool;

    case Variant::Ne:
        switch (type) {
        case Variant::Int:
            gen(iICmp);
            break;
        case Variant::Long:
            gen(iLCmp);
            break;
        case Variant::Float:
            gen(iFCmp);
            break;
        case Variant::Double:
            gen(iDCmp);
            break;

        default:
            break;
        }

        gen(iNe);

        return Variant::Bool;

    default:
        return Variant::Undefined;
    }
}

Variant CompilerContext::logicAnd(const Variant &lt, const Variant &rt) {
    toBool(lt, rt);
    gen(iLAnd);
    return Variant::Bool;
}

Variant CompilerContext::logicOr(const Variant &lt, const Variant &rt) {
    toBool(lt, rt);
    gen(iLOr);
    return Variant::Bool;
}

Variant CompilerContext::logicNot(const Variant &t) {
    cast(t, Variant::Bool);
    gen(iLNot);
    return Variant::Bool;
}

void CompilerContext::dec(string name) {
    if (hasLocal(name)) {
        cast(getLocal(name), Variant::Int);
        gen(iBIPush);
        gen(1);
        gen(iISub);
        setLocal(name, Variant::Int);
    } else if (parent)
        parent->dec(name);
}

void CompilerContext::inc(string name) {
    if (hasLocal(name)) {
        cast(getLocal(name), Variant::Int);
        gen(iBIPush);
        gen(1);
        gen(iIAdd);
        setLocal(name, Variant::Int);
    } else if (parent)
        parent->inc(name);
}

void CompilerContext::scan(string name) {
    if (hasLocal(name)) {
        switch (locals.at(name).type.type()) {
        case Variant::Bool:
            gen(iBScan);
            break;
        case Variant::Char:
            gen(iCScan);
            break;
        case Variant::Short:
            gen(iSScan);
            break;
        case Variant::Int:
            gen(iIScan);
            break;
        case Variant::Long:
            gen(iLScan);
            break;
        case Variant::Float:
            gen(iFScan);
            break;
        case Variant::Double:
            gen(iDScan);
            break;
        default:
            break;
        }

        store(name);
    } else if (parent)
        parent->scan(name);
}

void CompilerContext::print(const Variant &t) {
    switch (t.type()) {
    case Variant::Bool:
        gen(iBPrint);
        break;
    case Variant::Char:
        gen(iCPrint);
        break;
    case Variant::Short:
        gen(iSPrint);
        break;
    case Variant::Int:
        gen(iIPrint);
        break;
    case Variant::Long:
        gen(iLPrint);
        break;
    case Variant::Float:
        gen(iFPrint);
        break;
    case Variant::Double:
        gen(iDPrint);
        break;
    default:
        break;
    }
}

Variant CompilerContext::size(const Variant &t) {
    pop(t);
    return constant(t.size());
}

void CompilerContext::If(Node *condition, Node *body, Node *elseBody) {
    cast(condition->eval(this), Variant::Bool);

    gen(iJumpZ);
    int addr1 = compiler->offset();
    gen(0);
    gen(0);

    ignore(body->eval(this));

    int addr2;

    if (elseBody) {
        gen(iJump);
        addr2 = compiler->offset();
        gen(0);
        gen(0);
    }

    short offset = compiler->offset() - addr1;

    compiler->set(addr1, offset >> 8);
    compiler->set(addr1 + 1, offset);

    if (elseBody) {
        ignore(elseBody->eval(this));

        offset = compiler->offset() - addr2;

        compiler->set(addr2, offset >> 8);
        compiler->set(addr2 + 1, offset);
    }
}

void CompilerContext::While(Node *condition, Node *body) {
    int addr1 = compiler->offset();

    cast(condition->eval(this), Variant::Bool);

    gen(iJumpZ);
    int addr2 = compiler->offset();
    gen(0);
    gen(0);

    ignore(body->eval(this));

    gen(iJump);

    short offset = addr1 - compiler->offset();

    gen(offset >> 8);
    gen(offset);

    offset = compiler->offset() - addr2;

    compiler->set(addr2, offset >> 8);
    compiler->set(addr2 + 1, offset);
}

void CompilerContext::Do(Node *body, Node *condition) {
    int addr1 = compiler->offset();

    ignore(body->eval(this));

    cast(condition->eval(this), Variant::Bool);

    gen(iJumpNZ);

    short offset = addr1 - compiler->offset();

    gen(offset >> 8);
    gen(offset);
}

void CompilerContext::For(Node *preffix, Node *condition, Node *suffix, Node *body) {
    ignore(preffix->eval(this));

    int addr1 = compiler->offset();

    cast(condition->eval(this), Variant::Bool);

    gen(iJumpZ);
    int addr2 = compiler->offset();
    gen(0);
    gen(0);

    ignore(body->eval(this));
    ignore(suffix->eval(this));

    gen(iJump);

    short offset = addr1 - compiler->offset();

    gen(offset >> 8);
    gen(offset);

    offset = compiler->offset() - addr2;

    compiler->set(addr2, offset >> 8);
    compiler->set(addr2 + 1, offset);
}

Variant CompilerContext::getVoid() {
    return Variant::Void;
}

void CompilerContext::empty() {
    gen(iNop);
}

void CompilerContext::ignore(const Variant &v) {
    if (v.type() != Variant::Void)
        pop(v);
}

void CompilerContext::error(string message) {
    throw new CompilationError(message);
}

Variant CompilerContext::getLocal(string name) {
    load(name);
    return locals.at(name).type;
}

bool CompilerContext::setLocal(string name, const Variant &type) {
    if (hasLocal(name)) {
        if (locals.at(name).isConst)
            throw new CompilationError("assignment of read-only variable '" + name + "'");

        cast(type, locals.at(name).type.type());
        store(name);

        return true;
    }

    return false;
}

void CompilerContext::gen(byte op) {
    compiler->gen(op);
}

void CompilerContext::push(const Variant &value) {
    int v = *(int *)value.cast(Variant::Int).getValue();

    if (value.type() <= Variant::Long && abs(v) <= 0xff) {
        gen(iBIPush);
        gen(v);
        cast(Variant::Int, value.type());
    } else if (value.type() <= Variant::Long && abs(v) <= 0xffff) {
        gen(iSIPush);
        gen(v >> 8);
        gen(v);
        cast(Variant::Int, value.type());
    } else {
        switch (value.type()) {
        case Variant::Bool:
            gen(iBPush);
            break;
        case Variant::Char:
            gen(iCPush);
            break;
        case Variant::Short:
            gen(iSPush);
            break;
        case Variant::Int:
            gen(iIPush);
            break;
        case Variant::Long:
            gen(iLPush);
            break;
        case Variant::Float:
            gen(iFPush);
            break;
        case Variant::Double:
            gen(iDPush);
            break;
        default:
            break;
        }

        short index = compiler->constant(value);

        gen(index >> 8);
        gen(index);
    }
}

void CompilerContext::pop(const Variant &value) {
    switch (value.type()) {
    case Variant::Bool:
        gen(iBPop);
        break;
    case Variant::Char:
        gen(iBPop);
        break;
    case Variant::Short:
        gen(iSPop);
        break;
    case Variant::Int:
        gen(iIPop);
        break;
    case Variant::Long:
        gen(iLPop);
        break;
    case Variant::Float:
        gen(iIPop);
        break;
    case Variant::Double:
        gen(iLPop);
        break;
    default:
        break;
    }
}

void CompilerContext::load(string name) {
    switch (locals.at(name).type.type()) {
    case Variant::Bool:
        gen(iBLoad);
        break;
    case Variant::Char:
        gen(iCLoad);
        break;
    case Variant::Short:
        gen(iSLoad);
        break;
    case Variant::Int:
        gen(iILoad);
        break;
    case Variant::Long:
        gen(iLLoad);
        break;
    case Variant::Float:
        gen(iFLoad);
        break;
    case Variant::Double:
        gen(iDLoad);
        break;
    default:
        break;
    }

    short index = locals.at(name).index;

    gen(index >> 8);
    gen(index);
}

void CompilerContext::store(string name) {
    switch (locals.at(name).type.type()) {
    case Variant::Bool:
        gen(iBStore);
        break;
    case Variant::Char:
        gen(iCStore);
        break;
    case Variant::Short:
        gen(iSStore);
        break;
    case Variant::Int:
        gen(iIStore);
        break;
    case Variant::Long:
        gen(iLStore);
        break;
    case Variant::Float:
        gen(iFStore);
        break;
    case Variant::Double:
        gen(iDStore);
        break;
    default:
        break;
    }

    short index = locals.at(name).index;

    gen(index >> 8);
    gen(index);
}

Variant::Type CompilerContext::coerce(const Variant &lt, const Variant &rt) {
    Variant::Type type = Variant::coerce(lt.type(), rt.type());

    cast(rt, type);

    if (lt.type() != type) {
        gen(iSwap);
        gen((byte)lt.type() << 4 | (byte)type);

        cast(lt, type);

        gen(iSwap);
        gen((byte)type << 4 | (byte)type);
    }

    return type;
}

void CompilerContext::toBool(const Variant &lt, const Variant &rt) {
    cast(rt, Variant::Bool);

    gen(iSwap);
    gen((byte)lt.type() << 4 | (byte)Variant::Bool);

    cast(lt, Variant::Bool);

    gen(iSwap);
    gen((byte)Variant::Bool << 4 | (byte)Variant::Bool);
}
