#include "types.h"
/* normal 0x005036D0 -- clears bit 3 of the 0x1C flag word across `n` 0x20-byte
 * slots.  `bgezl $5` with `daddu $7,$0,$0` in the delay slot is the shared
 * `i = 0` duplicated into the negative-count arm, which clamps the count to 1.
 * The `addiu $4,$4,0x20` appears twice for the same reason (the scheduler
 * copies it into the `beql` delay slot); it is one source `p++`. */

typedef struct Slot { u8 pad00[0x1C]; u16 f1C; u8 pad1E[2]; } Slot;

void normal_BtlChgMenuSpritesClearFlag8_5036d0(Slot *p, s32 n)
{
    s32 i;

    if (p == 0) {
        return;
    }
    if (n < 0) {
        n = 1;
    }
    for (i = 0; i < n; i++) {
        u16 v = p->f1C;
        if ((v & 8) != 0) {
            p->f1C = v ^ 8;
        }
        p++;
    }
}
