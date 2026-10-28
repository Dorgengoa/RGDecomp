/* rgp:protos */
#define RGP_SELF_PadSetRepeat_183d50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* mask=1 is available before the two clamps (it fills the first delay slot);
   q is computed after them (it fills the second). */

void PadSetRepeat_183d50(u8 *p, u32 flags, s32 a, s32 b)
{
    s32 i;
    u32 mask = 1;
    u32 *q;

    if (b < 2) {
        b = 2;
    }
    if (a < 2) {
        a = 2;
    }
    q = (u32 *)(p + 0xC0);
    for (i = 0; i < 0x20; i++, mask <<= 1) {
        if ((flags & mask) != 0) {
            q[0] |= mask;
            q[1] &= ~mask;
            q[i + 2] = 0;
            q[i + 0x22] = a;
            q[i + 0x42] = b;
        }
    }
}
