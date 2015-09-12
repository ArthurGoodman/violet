#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

enum {
    iNone = -1,

#define X(a, b) a,
#include "instructions.def"
#undef X
};

#endif // INSTRUCTIONS_H

