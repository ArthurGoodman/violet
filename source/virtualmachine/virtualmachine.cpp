#include "virtualmachine.h"

#include "common.h"
#include "program.h"
#include "io.h"
#include "utility.h"
#include "instructions.h"
#include "runtimeerror.h"

vector<string> VirtualMachine::instructions = {
#define X(a, b) b,
#include "instructions.def"
#undef X
};

void VirtualMachine::run(Program *p) {
    this->p = p;

    stack.release();
    locals.release();

    locals.allocate(p->getLocalsSize());

    printProgram("bytecode.txt", p);

    byte *code = p->getCode().data();

    for (offset = 0; offset < p->getCode().size(); offset++) {
        switch (code[offset]) {
        case iNop:
            break;

        case iBIPush:
            push<int>(code[offset + 1]);
            offset += 1;
            break;
        case iSIPush:
            push<int>((short)((code[offset + 1] << 8) + code[offset + 2]));
            offset += 2;
            break;

        case iBPush:
            push(*(bool *)constant());
            offset += 2;
            break;
        case iCPush:
            push(*(char *)constant());
            offset += 2;
            break;
        case iSPush:
            push(*(short *)constant());
            offset += 2;
            break;
        case iIPush:
            push(*(int *)constant());
            offset += 2;
            break;
        case iLPush:
            push(*(long long *)constant());
            offset += 2;
            break;
        case iFPush:
            push(*(float *)constant());
            offset += 2;
            break;
        case iDPush:
            push(*(double *)constant());
            offset += 2;
            break;

        case iBPop:
            pop<bool>();
            break;
        case iSPop:
            pop<short>();
            break;
        case iIPop:
            pop<int>();
            break;
        case iLPop:
            pop<long long>();
            break;

        case iBLoad:
            push(*(bool *)local());
            offset += 2;
            break;
        case iCLoad:
            push(*(char *)local());
            offset += 2;
            break;
        case iSLoad:
            push(*(short *)local());
            offset += 2;
            break;
        case iILoad:
            push(*(int *)local());
            offset += 2;
            break;
        case iLLoad:
            push(*(long long *)local());
            offset += 2;
            break;
        case iFLoad:
            push(*(float *)local());
            offset += 2;
            break;
        case iDLoad:
            push(*(double *)local());
            offset += 2;
            break;

        case iBStore:
            *(bool *)local() = pop<bool>();
            offset += 2;
            break;
        case iCStore:
            *(char *)local() = pop<char>();
            offset += 2;
            break;
        case iSStore:
            *(short *)local() = pop<short>();
            offset += 2;
            break;
        case iIStore:
            *(int *)local() = pop<int>();
            offset += 2;
            break;
        case iLStore:
            *(long long *)local() = pop<long long>();
            offset += 2;
            break;
        case iFStore:
            *(float *)local() = pop<float>();
            offset += 2;
            break;
        case iDStore:
            *(double *)local() = pop<double>();
            offset += 2;
            break;

        case iICmp: {
            int b = pop<int>();
            int a = pop<int>();
            push<char>(a < b ? -1 : a == b ? 0 : 1);
        } break;
        case iLCmp: {
            long long b = pop<long long>();
            long long a = pop<long long>();
            push<char>(a < b ? -1 : a == b ? 0 : 1);
        } break;
        case iFCmp: {
            float b = pop<float>();
            float a = pop<float>();
            push<char>(a < b ? -1 : a == b ? 0 : 1);
        } break;
        case iDCmp: {
            double b = pop<double>();
            double a = pop<double>();
            push<char>(a < b ? -1 : a == b ? 0 : 1);
        } break;

        case iLt:
            push<bool>(pop<char>() < 0);
            break;
        case iGt:
            push<bool>(pop<char>() > 0);
            break;
        case iLe:
            push<bool>(pop<char>() <= 0);
            break;
        case iGe:
            push<bool>(pop<char>() >= 0);
            break;
        case iEq:
            push<bool>(pop<char>() == 0);
            break;
        case iNe:
            push<bool>(pop<char>() != 0);
            break;

        case iIAdd:
            push(pop<int>() + pop<int>());
            break;
        case iLAdd:
            push(pop<long long>() + pop<long long>());
            break;
        case iFAdd:
            push(pop<float>() + pop<float>());
            break;
        case iDAdd:
            push(pop<double>() + pop<double>());
            break;

        case iISub: {
            int b = pop<int>();
            int a = pop<int>();
            push(a - b);
        } break;
        case iLSub: {
            long long b = pop<long long>();
            long long a = pop<long long>();
            push(a - b);
        } break;
        case iFSub: {
            float b = pop<float>();
            float a = pop<float>();
            push(a - b);
        } break;
        case iDSub: {
            double b = pop<double>();
            double a = pop<double>();
            push(a - b);
        } break;

        case iIMul:
            push(pop<int>() * pop<int>());
            break;
        case iLMul:
            push(pop<long long>() * pop<long long>());
            break;
        case iFMul:
            push(pop<float>() * pop<float>());
            break;
        case iDMul:
            push(pop<double>() * pop<double>());
            break;

        case iIDiv: {
            int b = pop<int>();
            int a = pop<int>();

            if (b == 0)
                throw new RuntimeError("division by zero");

            push(a / b);
        } break;
        case iLDiv: {
            long long b = pop<long long>();
            long long a = pop<long long>();

            if (b == 0)
                throw new RuntimeError("division by zero");

            push(a / b);
        } break;
        case iFDiv: {
            float b = pop<float>();
            float a = pop<float>();
            push(a / b);
        } break;
        case iDDiv: {
            double b = pop<double>();
            double a = pop<double>();
            push(a / b);
        } break;

        case iIMod: {
            int b = pop<int>();
            int a = pop<int>();

            if (b == 0)
                throw new RuntimeError("division by zero");

            push(a % b);
        } break;
        case iLMod: {
            long long b = pop<long long>();
            long long a = pop<long long>();

            if (b == 0)
                throw new RuntimeError("division by zero");

            push(a % b);
        } break;
        case iFMod: {
            float b = pop<float>();
            float a = pop<float>();
            push(fmodf(a, b));
        } break;
        case iDMod: {
            double b = pop<double>();
            double a = pop<double>();
            push(fmod(a, b));
        } break;

        case iLAnd: {
            bool b = pop<bool>();
            bool a = pop<bool>();
            push<bool>(a && b);
        } break;
        case iLOr: {
            bool b = pop<bool>();
            bool a = pop<bool>();
            push<bool>(a || b);
        } break;
        case iLNot:
            push<bool>(!pop<bool>());
            break;

        case iSwap: {
            Variant::Type at = (Variant::Type)(code[offset + 1] >> 4), bt = (Variant::Type)(code[offset + 1] & 0xf);

            const Variant &bv = popVariant(bt);
            const Variant &av = popVariant(at);

            pushVariant(bv);
            pushVariant(av);

            offset += 1;
        } break;
        case iCast: {
            Variant::Type from = (Variant::Type)(code[offset + 1] >> 4), to = (Variant::Type)(code[offset + 1] & 0xf);
            pushVariant(popVariant(from).cast(to));
            offset += 1;
        } break;

        case iJump:
            offset += (short)((code[offset + 1] << 8) + code[offset + 2]);
            break;
        case iJumpZ:
            offset += pop<bool>() ? 2 : (short)((code[offset + 1] << 8) + code[offset + 2]);
            break;
        case iJumpNZ:
            offset += pop<bool>() ? (short)((code[offset + 1] << 8) + code[offset + 2]) : 2;
            break;

        case iBPrint:
            IO::print(Utility::toString(pop<bool>()));
            break;
        case iCPrint:
            IO::print(Utility::toString(pop<char>()));
            break;
        case iSPrint:
            IO::print(Utility::toString(pop<short>()));
            break;
        case iIPrint:
            IO::print(Utility::toString(pop<int>()));
            break;
        case iLPrint:
            IO::print(Utility::toString(pop<long long>()));
            break;
        case iFPrint:
            IO::print(Utility::toString(pop<float>()));
            break;
        case iDPrint:
            IO::print(Utility::toString(pop<double>()));
            break;

        case iBScan: {
            bool v;
            IO::scan(v);
            push(v);
        } break;
        case iCScan: {
            char v;
            IO::scan(v);
            push(v);
        } break;
        case iSScan: {
            short v;
            IO::scan(v);
            push(v);
        } break;
        case iIScan: {
            int v;
            IO::scan(v);
            push(v);
        } break;
        case iLScan: {
            long long v;
            IO::scan(v);
            push(v);
        } break;
        case iFScan: {
            float v;
            IO::scan(v);
            push(v);
        } break;
        case iDScan: {
            double v;
            IO::scan(v);
            push(v);
        } break;
        }
    }
}

byte *VirtualMachine::constant() {
    return p->getConstants().data() + (short)((p->getCode().data()[offset + 1] << 8) + p->getCode().data()[offset + 2]);
}

byte *VirtualMachine::local() {
    return locals.data() + (short)((p->getCode().data()[offset + 1] << 8) + p->getCode().data()[offset + 2]);
}

void VirtualMachine::printProgram(string fileName, Program *p) {
    string text;

    byte *code = p->getCode().data();

    text += "Code:\n";

    for (int i = 0; i < p->getCode().size(); i++) {
        text += "  " + instructions[code[i]];

        switch (code[i]) {
        case iBIPush:
            text += " " + Utility::toString((short)code[i + 1]);
            i += 1;
            break;

        case iSIPush:
            text += " " + Utility::toString((unsigned short)((code[i + 1] << 8) + code[i + 2]));
            i += 2;
            break;

        case iBPush:
        case iCPush:
        case iSPush:
        case iIPush:
        case iLPush:
        case iFPush:
        case iDPush:
        case iBLoad:
        case iCLoad:
        case iSLoad:
        case iILoad:
        case iLLoad:
        case iFLoad:
        case iDLoad:
        case iBStore:
        case iCStore:
        case iSStore:
        case iIStore:
        case iLStore:
        case iFStore:
        case iDStore:
        case iJump:
        case iJumpZ:
        case iJumpNZ:
            text += " " + Utility::toString((short)((code[i + 1] << 8) + code[i + 2]));
            i += 2;
            break;

        case iCast:
        case iSwap:
            text += " " + Variant((Variant::Type)(code[i + 1] >> 4)).toString() + " " + Variant((Variant::Type)(code[i + 1] & 0xf)).toString();
            i += 1;
            break;
        }

        text += "\n";
    }

    byte *constants = p->getConstants().data();

    text += "\nConstants:\n";

    for (int i = 0; i < p->getConstants().size(); i++)
        text += "  " + Utility::toString(i) + ": " + Utility::toString((int)constants[i]) + "\n";

    IO::writeFile(fileName, text);
}

void VirtualMachine::pushVariant(const Variant &value) {
    switch (value.type()) {
    case Variant::Bool:
        push(*(bool *)value.getValue());
        break;
    case Variant::Char:
        push(*(char *)value.getValue());
        break;
    case Variant::Short:
        push(*(short *)value.getValue());
        break;
    case Variant::Int:
        push(*(int *)value.getValue());
        break;
    case Variant::Long:
        push(*(long long*)value.getValue());
        break;
    case Variant::Float:
        push(*(float *)value.getValue());
        break;
    case Variant::Double:
        push(*(double *)value.getValue());
        break;
    default:
        break;
    }
}

Variant VirtualMachine::popVariant(Variant::Type type) {
    switch (type) {
    case Variant::Bool:
        return pop<bool>();
        break;
    case Variant::Char:
        return pop<char>();
        break;
    case Variant::Short:
        return pop<short>();
        break;
    case Variant::Int:
        return pop<int>();
        break;
    case Variant::Long:
        return pop<long long>();
        break;
    case Variant::Float:
        return pop<float>();
        break;
    case Variant::Double:
        return pop<double>();
        break;
    default:
        return Variant();
    }
}
