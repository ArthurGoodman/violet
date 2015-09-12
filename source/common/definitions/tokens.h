#ifndef TOKENS_H
#define TOKENS_H

enum {
    tNone = -1,

#define X(a, b) a,
#include "operators.def"
#include "keywords.def"
#include "othertokens.def"
#undef X
};

#endif // TOKENS_H
