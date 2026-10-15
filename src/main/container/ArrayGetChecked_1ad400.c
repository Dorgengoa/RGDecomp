#include "types.h"

typedef struct E_001ad400 { u8 b[368]; } E_001ad400;

typedef struct S_001ad400 {
    u8 pad0[0x204];
    s32 n;
    E_001ad400 *p;
} S_001ad400;

E_001ad400 *ArrayGetChecked_1ad400(S_001ad400 *self, s32 i)
{
    s32 n;
    E_001ad400 *p = self->p;
    if (p == 0) goto zero1;
    n = self->n;
    if (n != 0) goto g2;
zero1:
    return 0;
g2:
    if (i < 0) goto zero;
    if (i < n) goto ok;
zero:
    return 0;
ok:
    return &p[i];
}
