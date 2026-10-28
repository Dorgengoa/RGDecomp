/* rgp:protos */
#define RGP_SELF_ZonePhaseMatrixQueryGetAt_414450 1
#include "port/game_protos.h"
#line 1
#include "types.h"

#pragma divbyzerocheck on

struct TFUN_00414450 { u8 pad000[0x4]; void *f04; s16 f08; };

/*rgp*/

s32 ZonePhaseMatrixQueryGetAt_414450(struct TFUN_00414450 *p, void *a)
{
    void *q;

    s16 v;

    q = p->f04;
    if (q == 0) return 0;
    v = p->f08;
    return ((s32)ZonePhaseMatrixFindNthByKey_414530(q, (s16)(v / 100), v, a));
}
