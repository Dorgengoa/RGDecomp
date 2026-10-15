#include "types.h"

typedef struct N_00190930 {
    struct N_00190930 *f0;
} N_00190930;

typedef struct S_00190930 {
    u8 pad0[4];
    N_00190930 **f4;
} S_00190930;

s32 FuncDataTableCountBucket_190930(S_00190930 *self, s32 i)
{
    N_00190930 **p;
    N_00190930 *q;
    N_00190930 *t;
    s32 c;
    p = self->f4;
    if (p != 0) goto g1;
    return 0;
g1:
    if (i < 0) goto zero;
    if (i < 13) goto ok;
zero:
    return 0;
ok:
    q = p[i];
    if (q == 0) return 0;
    c = 1;
    t = q->f0;
    while (t != 0) {
        t = t->f0;
        c++;
    }
    return c;
}
