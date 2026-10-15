#include "types.h"

typedef struct E_0042a330 { u8 b[148]; } E_0042a330;

typedef struct S_0042a330 {
    u8 pad0[4];
    E_0042a330 *f4;
    u8 pad8[2];
    u16 fA_lo : 2;
    u16 n : 14;
} S_0042a330;

E_0042a330 *ResGroupListGetElem_42a330(S_0042a330 *self, s32 i)
{
    E_0042a330 *p;
    if (i < 0) goto zero;
    if (self->n > i) {
        p = self->f4;
        if (p != 0) goto ok;
    }
zero:
    return 0;
ok:
    return &p[i];
}
