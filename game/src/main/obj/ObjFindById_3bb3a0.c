/* rgp:protos */
#define RGP_SELF_ObjFindById_3bb3a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E_003bb3a0 {
    u8 pad0[0xC];
    s32 fC;
} E_003bb3a0;

typedef struct T_003bb3a0 {
    u8 pad0[0x14];
    s32 f14;
    u8 pad18[4];
    s32 f1C;
} T_003bb3a0;

typedef struct S_003bb3a0 {
    u8 pad0[8];
    s32 f8;
    u8 padC[4];
    T_003bb3a0 *f10;
} S_003bb3a0;

/*rgp*/

E_003bb3a0 *ObjFindById_3bb3a0(S_003bb3a0 *self, s32 key)
{
    E_003bb3a0 *r;
    E_003bb3a0 *e;
    T_003bb3a0 *t;
    s32 cnt;
    s32 n;
    s32 i;
    if (key < 0) return 0;
    if (self->f8 == 0) goto zeroA;
    t = self->f10;
    if (t != 0) goto g1;
zeroA:
    return 0;
g1:
    cnt = t->f1C;
    if (cnt > 0) goto g2;
    return 0;
g2:
    n = t->f14;
    r = 0;
    for (i = 0; i < n; i++) {
        e = ((E_003bb3a0 *)PoolGetUsedElem_36acb0(self->f10, i));
        if (e == 0) continue;
        if (key == e->fC) {
            r = e;
            break;
        }
        cnt--;
        if (cnt <= 0) break;
    }
    return r;
}
