#include "types.h"
/* insect 0x005140C0 -- 36 bytes, 9 instructions. */

void insect_InsectTeamSlotSetCell_5140c0(s32 i, u8 *p, u8 v, s32 f)
{
    u8 *q = p + i;
    u8 *r = q + 0xA;

    q[0xA] = v;
    if (f != 0) {
        *r |= 0x80;
    }
}
