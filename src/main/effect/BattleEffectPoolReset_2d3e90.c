#include "types.h"

extern void BattleEffectBurstReset_2d3f00(void *);

void BattleEffectPoolReset_2d3e90(void *p)
{
    s32 i;
    u8 *q;

    q = *(u8 **)p;
    i = 0;
    while (i < *(s16 *)((u8 *)p + 4)) {
        BattleEffectBurstReset_2d3f00(q);
        i++;
        q += 0x1020;
    }
}
