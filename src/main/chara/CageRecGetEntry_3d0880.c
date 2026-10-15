#include "types.h"

typedef struct E_003d0880 { u8 b[124]; } E_003d0880;

typedef struct P_003d0880 {
    u8 padA[0xA];
    s16 fA;
    u8 padC[0x20];
    E_003d0880 arr[1];
} P_003d0880;

typedef struct S_003d0880 {
    u8 pad18[0x18];
    P_003d0880 *f18;
} S_003d0880;

E_003d0880 *CageRecGetEntry_3d0880(S_003d0880 *self, s32 i)
{
    P_003d0880 *p;
    if (i < 0) goto zero;
    p = self->f18;
    if (i < p->fA) goto ok;
zero:
    return 0;
ok:
    return &p->arr[i];
}
