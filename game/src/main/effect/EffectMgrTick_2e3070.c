/* rgp:protos */
#define RGP_SELF_EffectMgrTick_2e3070 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

void EffectMgrTick_2e3070(void *p)
{
    if (*(s16 *)((s32)p + 0x4078) == 0) return;
    EffectResTickExpireAll_2e13e0(p);
    EffectEntriesUpdate_2deb30((void *)((s32)p + 0x1674));
    EffTableUpdate_1a0620((void *)((s32)p + 0x58), 1.0f);
}
