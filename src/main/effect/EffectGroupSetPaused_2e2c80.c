#include "types.h"

extern s32 EffectIsLoadedByName_2dff60(u8 *base, u8 *p);
extern void EffDefSetPaused_1a0a10(u8 *p, s32 v, s32 flag);
extern void EffectEntriesSetPausedByGroup_2dd840(u8 *p, s32 key, u8 f);

void EffectGroupSetPaused_2e2c80(u8 *base, s32 key, s32 flag)
{
    s32 i;
    u8 *e;

    for (i = 0; i < 0x30; i++) {
        e = base + i * 0x70;
        if (*(s32 *)(e + 0x1C8) != key) continue;
        if (EffectIsLoadedByName_2dff60(base, e + 0x1A4) == 0) continue;
        EffDefSetPaused_1a0a10(base + 0x58, *(s32 *)(e + 0x178), flag);
    }
    EffectEntriesSetPausedByGroup_2dd840(base + 0x1674, key, flag);
}
