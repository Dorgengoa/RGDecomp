#include "types.h"

#pragma divbyzerocheck on

struct TFUN_004144a0 { u8 pad000[0x4]; void *f04; s16 f08; };

extern s32 ZonePhaseMatrixCountByKey_414620(void *q, s16 k, s16 v);

s32 ZonePhaseMatrixQueryCount_4144a0(struct TFUN_004144a0 *p)
{
    void *q;
    s16 v;

    q = p->f04;
    if (q == 0) return 0;
    v = p->f08;
    return ZonePhaseMatrixCountByKey_414620(q, (s16)(v / 100), v);
}
