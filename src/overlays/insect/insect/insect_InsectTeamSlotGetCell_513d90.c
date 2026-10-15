#include "types.h"
/* insect 0x00513D90 -- 100 bytes.  The byte at +0xA is loaded TWICE because
 * the stores through *pf stand between the two uses (insect-load-across-store,
 * read from the other side: the reload is forced, not a spelling choice).
 * Its ADDRESS, though, is a NAMED POINTER: retail spends one `addiu $5,$3,0xA`
 * that the `p[0xA]` displacement form never emits. */

void insect_InsectTeamSlotGetCell_513d90(s32 i, u8 *base, s32 *pv, s32 *pf, s32 mode)
{
    u8 *p;
    u8 *q;

    p = base + i;
    q = p + 0xA;
    *pf = 0;
    if (*q & 0x80) {
        *pf = 1;
    }
    if (mode == 0) {
        *pf += 5;
    }
    if (mode == 1) {
        *pf = 1 - *pf;
    }
    *pv = *q & ~0x80;
}
