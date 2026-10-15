#include "types.h"

#pragma divbyzerocheck on

struct TFUN_00414a50 { u8 pad000[0x4]; void *f04; s16 f08; };

extern s32 ZonePhaseSetCountByKey_414c60(void *q, s16 k, s16 v);

s32 ZonePhaseSetQueryCount_414a50(struct TFUN_00414a50 *p)
{
    void *q;
    s16 v;

    q = p->f04;
    if (q == 0) return 0;
    v = p->f08;
    return ZonePhaseSetCountByKey_414c60(q, (s16)(v / 100), v);
}
