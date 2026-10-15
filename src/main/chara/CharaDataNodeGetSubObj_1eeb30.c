#include "types.h"

typedef struct E_001eeb30 { u8 b[1936]; } E_001eeb30;

typedef struct S_001eeb30 {
    u8 pad0[0x2A];
    s16 n;
    E_001eeb30 *p;
} S_001eeb30;

E_001eeb30 *CharaDataNodeGetSubObj_1eeb30(S_001eeb30 *self, s32 i)
{
    E_001eeb30 *p;
    if (i < 0) goto zero;
    if (i < self->n) goto ok;
zero:
    return 0;
ok:
    p = self->p;
    if (p == 0) return 0;
    return &p[i];
}
