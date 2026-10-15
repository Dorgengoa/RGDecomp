#include "types.h"

extern void EffectResTickExpireAll_2e13e0(void *);
extern void EffectEntriesUpdate_2deb30(void *);
extern void EffTableUpdate_1a0620(void *, f32);

void EffectMgrTick_2e3070(void *p)
{
    if (*(s16 *)((s32)p + 0x4078) == 0) return;
    EffectResTickExpireAll_2e13e0(p);
    EffectEntriesUpdate_2deb30((void *)((s32)p + 0x1674));
    EffTableUpdate_1a0620((void *)((s32)p + 0x58), 1.0f);
}
