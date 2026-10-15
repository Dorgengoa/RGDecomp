#include "types.h"

struct T2D3C60 { u8 *f00; s16 f04; };

extern void BattleEffectBurstSpawn_2d4760(u8 *e, void *a);

void BattleEffectSpawnInFreeSlot_2d3c60(struct T2D3C60 *p, void *a)
{
    u8 *base;
    s16 n;
    s32 i;
    u8 *e;

    base = p->f00;
    if (base == 0) return;
    n = p->f04;
    for (i = 0; i < n; i++) {
        e = base + i * 4128;
        if (*(s32 *)e == 0) {
            BattleEffectBurstSpawn_2d4760(e, a);
            return;
        }
    }
}
