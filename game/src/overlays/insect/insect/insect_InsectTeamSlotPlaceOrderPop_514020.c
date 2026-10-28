/* rgp:protos */
#define RGP_SELF_insect_InsectTeamSlotPlaceOrderPop_514020 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00514020 -- 56 bytes, 14 instructions, no calls.
 *
 * A downward scan of a[19..15].  `addu $2,$4,$6` then `addiu $5,$2,0xF`, with
 * the LOAD through the intermediate (`lb $2,0xF($2)`) and the STORE through
 * the named pointer, is the left-associative pointer sum `p = a + i + 15`
 * (ixa07's lever 2, measured on the neighbouring insect_InsectTeamSlotPlaceOrderPush_514060). */

s8 insect_InsectTeamSlotPlaceOrderPop_514020(s8 *a)
{
    s32 i;
    s8 *p;
    s8  v;

    for (i = 4; i >= 0; i--) {
        p = a + i + 15;
        v = *p;
        if (v != -1) {
            *p = -1;
            return v;
        }
    }
    return -1;
}
