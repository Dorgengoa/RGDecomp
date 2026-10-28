/* rgp:protos */
#define RGP_SELF_insect_InsectBattlePopState_50d880 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0050d880 -- 64 B / 16 words.  Twin pair 0050d760 / 0050d880, differing
 * only in the row array (0x5E34 vs 0x5DD4) and hence in the scan callee.
 *
 * The `b .L<tail>` out of the if-body with the store in its delay slot is the
 * `break`; the loop's own fall-out lands on the SAME label, so both paths reach
 * one tail call -- retail emits `j insect_InsectBattleGetState_50d6f0` with `daddu $5,$0,$0`
 * in the delay slot, i.e. `return 0050d6f0(o, 0);`.
 */

typedef struct Ins {
    u8 pad000[0x5DD4];
    s8 f5DD4[12][8];            /* +0x5DD4 */
    s8 f5E34[12][8];            /* +0x5E34 */
} Ins;

/*rgp*/

s32 insect_InsectBattlePopState_50d880(Ins *o, s32 k)
{
    s32 i;

    for (i = 7; i >= 0; i--) {
        if (o->f5DD4[k][i] != -1) {
            o->f5DD4[k][i] = -1;
            break;
        }
    }
    return insect_InsectBattleGetState_50d6f0(o, 0);
}
