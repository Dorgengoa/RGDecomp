#include "types.h"

typedef struct S_001de460 {
    u8 pad0[4];
    void **f4;
    s16 f8;
    s16 fA;
} S_001de460;

s32 MapPartTableAddUnique_1de460(S_001de460 *self, void *v)
{
    void **p;
    void **q;
    s32 n;
    s32 m;
    s32 j;
    if (v == 0) goto zero;
    p = self->f4;
    if (p == 0) goto zero;
    n = self->f8;
    m = self->fA;
    if (m > n) goto ok;
zero:
    return 0;
ok:
    q = p;
    j = 0;
    while (j < n) {
        if (*q == v) return 0;
        j++;
        q++;
    }
    p[n] = v;
    self->f8 = self->f8 + 1;
    return 1;
}
