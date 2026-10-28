/* rgp:protos */
#define RGP_SELF_HpGaugeSetSlotHop_31e8b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

void HpGaugeSetSlotHop_31e8b0(void *p, s32 a, s8 v)
{
    s32 i;
    s8 *base;
    s8 *q;

    i = FindS16Index16_31e870(p, a);
    if (i == -1) return;
    base = (s8 *)(i + (s32)p);
    q = base + 0x210;
    if (*q > 0) return;
    *q = v;
}
