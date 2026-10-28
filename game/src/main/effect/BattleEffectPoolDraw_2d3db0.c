/* rgp:protos */
#define RGP_SELF_BattleEffectPoolDraw_2d3db0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

void BattleEffectPoolDraw_2d3db0(void *p)
{
    s32 i;
    u8 *q;

    DrawListAddTexLoad_1418c0(GetDrawCtx_15de80(), 0x2A5, 1.0f);
    q = *(u8 **)p;
    i = 0;
    while (i < *(s16 *)((u8 *)p + 4)) {
        BattleEffectBurstDraw_2d4260(q);
        i++;
        q += 0x1020;
    }
}
