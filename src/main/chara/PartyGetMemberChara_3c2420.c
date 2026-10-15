#include "types.h"

struct G3C2420 { u8 pad000[0x14]; void *f14; };

extern struct G3C2420 *D_00483890;
extern s32 CharaMgrPoolFindById_3a8c60(void *a, s32 k);

s32 PartyGetMemberChara_3c2420(u8 *p, s32 i)
{
    struct G3C2420 *g;
    s32 n;

    g = D_00483890;
    if (g == 0) return 0;
    n = *(s16 *)(p + 0x18C);
    if (i >= 0) {
        if (i < n) goto ok;
    }
    i = -1;
    goto join;
ok:
    i = ((s16 *)(p + 0x190))[i];
join:
    if (i < 0) return 0;
    return CharaMgrPoolFindById_3a8c60(g->f14, i);
}
