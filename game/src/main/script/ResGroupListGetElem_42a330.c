/* rgp:protos */
#define RGP_SELF_ResGroupListGetElem_42a330 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E_0042a330 { u8 b[148]; } E_0042a330;

typedef struct S_0042a330 {
    u8 pad0[4];
    E_0042a330 *f4;
    u8 pad8[2];
    __extension__ unsigned short fA_lo : 2;
    unsigned short n : 14;
} __attribute__((aligned(2))) S_0042a330;

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
