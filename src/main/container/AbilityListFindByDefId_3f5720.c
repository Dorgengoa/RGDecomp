#include "types.h"

typedef struct T_003f5720 {
    s16 f0;
} T_003f5720;

typedef struct E_003f5720 {
    u8 pad0[4];
    T_003f5720 *f4;
    u8 pad8[4];
} E_003f5720;

typedef struct S_003f5720 {
    u8 pad0[8];
    s32 f8;
    E_003f5720 *fC;
} S_003f5720;

E_003f5720 *AbilityListFindByDefId_3f5720(S_003f5720 *self, s32 key)
{
    E_003f5720 *p = self->fC;
    T_003f5720 *q;
    s32 n;
    s32 j;
    if (p == 0) goto zero;
    n = self->f8;
    if (n > 0) goto ok;
zero:
    return 0;
ok:
    j = 0;
    while (j < n) {
        q = p->f4;
        if (q != 0) {
            if (q->f0 == key) return p;
        }
        j++;
        p++;
    }
    return 0;
}
