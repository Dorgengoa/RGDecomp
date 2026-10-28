/* rgp:protos */
#define RGP_SELF_CharaMgrPoolFindById_3a8c60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E_003a8c60 {
    u8 pad0[0xC];
    s32 fC;
} E_003a8c60;

typedef struct T_003a8c60 {
    u8 pad0[0x14];
    s32 f14;
    u8 pad18[4];
    s32 f1C;
} T_003a8c60;

typedef struct S_003a8c60 {
    u8 pad0[8];
    T_003a8c60 *f8;
} S_003a8c60;

extern s32 D_004837EC;

/*rgp*/

E_003a8c60 *CharaMgrPoolFindById_3a8c60(S_003a8c60 *self, s32 key)
{
    E_003a8c60 *r;
    E_003a8c60 *e;
    T_003a8c60 *t;
    s32 cnt;
    s32 n;
    s32 i;
    if (key < 0) return 0;
    if (D_004837EC == 0) goto zeroA;
    t = self->f8;
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
        e = ((E_003a8c60 *)PoolGetUsedElem_36acb0(self->f8, i));
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
