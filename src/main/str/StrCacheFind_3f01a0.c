#include "types.h"

extern s32 D_004644F0[];

typedef struct E_003f01a0 {
    s16 f0;
    s16 f2;
    s32 f4;
    s32 f8;
} E_003f01a0;

typedef struct S_003f01a0 {
    u8 pad0[0x2C];
    void *f2C;
    E_003f01a0 *f30;
} S_003f01a0;

s32 StrCacheFind_3f01a0(S_003f01a0 *self, s32 k1, s32 k2, s32 k3)
{
    E_003f01a0 *p;
    E_003f01a0 *e;
    s32 n;
    s32 j;
    if (self->f2C == 0) goto zero;
    p = self->f30;
    if (p != 0) goto ok;
zero:
    return 0;
ok:
    n = D_004644F0[0];
    for (j = 0; j < n; j++) {
        e = &p[j];
        if (e->f0 != k1) continue;
        if (e->f4 != k2) continue;
        if (e->f2 != k3) continue;
        return e->f8;
    }
    return 0;
}
