/* rgp:protos */
#define RGP_SELF_BattleEffectBurstReset_2d3f00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

void BattleEffectBurstReset_2d3f00(u8 *base)
{
    u8 *p;
    s32 i;

    p = base + 0x20;
    for (i = 0; i < 0x40; i++) {
        p[0x34] = 0;
        p += 0x40;
    }
}
