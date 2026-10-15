#include "types.h"

struct T33C100 { u8 *f00; s16 f04; u8 pad006[0x2]; s32 f08; };

extern void StatusEffectSlotDraw_33c580(u8 *q, s16 k);

void StatusEffectDraw_33c100(struct T33C100 *p)
{
    u8 *q;
    s32 i;

    if (p->f08 == 0) return;
    q = p->f00;
    for (i = 0; i < 0x10; i++) {
        StatusEffectSlotDraw_33c580(q, p->f04);
        q += 0xE0;
    }
}
