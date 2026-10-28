/* rgp:protos */
#define RGP_SELF_BattleEffectPoolUpdate_2d3e30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

void BattleEffectPoolUpdate_2d3e30(void *p)
{
    s32 i;
    u8 *q;

    q = *(u8 **)p;
    i = 0;
    while (i < *(s16 *)((u8 *)p + 4)) {
        BattleEffectBurstUpdate_2d3f60(q);
        i++;
        q += 0x1020;
    }
}
