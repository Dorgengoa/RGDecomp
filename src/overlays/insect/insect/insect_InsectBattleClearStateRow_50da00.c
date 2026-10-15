#include "types.h"
/* insect 0x0050da00 -- 52 B / 13 words.  Twin pair, row array only.
 * A plain ascending clear of the 8-entry row.  The -1 and the row base are both
 * hoisted before the loop; the hoist of -1 lands in $4, clobbering the incoming
 * `o`, so nothing after the loop may touch `o` -- the function is void.
 */

typedef struct Ins {
    u8 pad000[0x5DD4];
    s8 f5DD4[12][8];            /* +0x5DD4 */
    s8 f5E34[12][8];            /* +0x5E34 */
} Ins;

void insect_InsectBattleClearStateRow_50da00(Ins *o, s32 k)
{
    s32 i;

    for (i = 0; i < 8; i++) {
        o->f5DD4[k][i] = -1;
    }
}
