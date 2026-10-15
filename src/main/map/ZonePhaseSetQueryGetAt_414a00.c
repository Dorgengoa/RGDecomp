#include "types.h"

#pragma divbyzerocheck on

struct TFUN_00414a00 { u8 pad000[0x4]; void *f04; s16 f08; };

extern s32 ZonePhaseSetFindNthByKey_414b70(void *q, s16 k, s16 v, void *a);

s32 ZonePhaseSetQueryGetAt_414a00(struct TFUN_00414a00 *p, void *a)
{
    void *q;

    s16 v;

    q = p->f04;
    if (q == 0) return 0;
    v = p->f08;
    return ZonePhaseSetFindNthByKey_414b70(q, (s16)(v / 100), v, a);
}
