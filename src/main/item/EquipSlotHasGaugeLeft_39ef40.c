#include "types.h"
/* `addiu $2,$0,1` sits in a PLAIN `bc1f` slot, so the 1 is written on both
   paths: the flag starts at 1 and the failing arm clears it. */
typedef struct P39EF40 { u8 pad000[0x10]; f32 m10; } P39EF40;
s32 EquipSlotHasGaugeLeft_39ef40(P39EF40 *p)
{
    s32 r;

    r = 1;
    if (p->m10 <= 0.0f) {
        r = 0;
    }
    return r;
}
