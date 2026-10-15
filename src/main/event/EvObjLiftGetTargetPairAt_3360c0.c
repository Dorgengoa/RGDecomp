#include "types.h"

typedef struct E { u8 b[104]; } E;

typedef struct S {
    u8 pad0[224];
    E *p;
    u8 pad1[4];
    s16 n;
} S;

E * EvObjLiftGetTargetPairAt_3360c0(S *self, s32 i)
{
    E *p = self->p;
    if (p == 0) goto zero;
    if (i < 0) goto zero;
    if (self->n > i) goto ok;
zero:
    return 0;
ok:
    return &p[i];
}
