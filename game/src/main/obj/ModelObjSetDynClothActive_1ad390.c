/* rgp:protos */
#define RGP_SELF_ModelObjSetDynClothActive_1ad390 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E_001ad390 {
    s32 f0;
    u8 pad4[364];
} E_001ad390;

typedef struct S_001ad390 {
    u8 pad0[0x204];
    s32 n;
    E_001ad390 *p;
} S_001ad390;

void ModelObjSetDynClothActive_1ad390(S_001ad390 *self, s32 i, s32 v)
{
    s32 n;
    E_001ad390 *p;
    E_001ad390 *e;
    p = self->p;
    if (p == 0) goto zero1;
    n = self->n;
    if (n != 0) goto g2;
zero1:
    e = 0;
    goto out;
g2:
    if (i < 0) goto zero;
    if (i < n) goto ok;
zero:
    e = 0;
    goto out;
ok:
    e = &p[i];
out:
    if (e == 0) return;
    e->f0 = v;
}
