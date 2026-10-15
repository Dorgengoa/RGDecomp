#include "types.h"
/* insect 0x0051DBE0 -- 68 bytes, 17 instructions.  TWO counters live at once
 * ($2 and $7) even though they hold the same value, so the source carries a
 * separate result count beside the loop index; the count is incremented in the
 * `bnel` delay slot, i.e. AFTER the `if` body. */

s32 insect_InsectBattleEffectsAddSlot_51dbe0(s32 *a, s32 v)
{
    s32 n;
    s32 i;

    n = 0;
    for (i = 0; i < 15; i++) {
        if (a[i + 2] == 0) {
            a[i + 2] = v;
            return n;
        }
        n++;
    }
    return -1;
}
