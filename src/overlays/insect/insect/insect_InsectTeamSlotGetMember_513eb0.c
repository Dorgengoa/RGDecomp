#include "types.h"
/* insect 0x00513EB0 -- 32 bytes, 8 instructions.  `addu $4, $5, $4` has the
 * POINTER in rs, so the pointer is parameter two and the index parameter one.
 * -1 is a NAMED RESULT LOCAL, not an early return: the early-return spelling
 * gives `bnel` with the `lb` annulled (7 words); the result variable gives
 * retail's plain `beq` + `nop` + `lb` (8 words). */

s32 insect_InsectTeamSlotGetMember_513eb0(s32 i, s8 *p)
{
    s8 *q = p + i;
    s32 r;

    r = -1;
    if (q[5] != -1) {
        r = q[0];
    }
    return r;
}
