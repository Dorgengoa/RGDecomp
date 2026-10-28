/* rgp:protos */
#define RGP_SELF_BattleEffectPoolReset_2d3e90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

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
