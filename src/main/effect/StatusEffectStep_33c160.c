#include "types.h"

struct T33C160 { u8 *f00; u8 pad004[0x4]; s32 f08; };

extern void StatusEffectSlotUpdate_33c3d0(u8 *q);

void StatusEffectStep_33c160(struct T33C160 *p)
{
    u8 *q;
    s32 i;

    if (p->f08 == 0) return;
    q = p->f00;
    for (i = 0; i < 0x10; i++) {
        StatusEffectSlotUpdate_33c3d0(q);
        q += 0xE0;
    }
}
