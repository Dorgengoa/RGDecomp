/* rgp:protos */
#define RGP_SELF_insect_InsectTeamSlotIsFull_513f10 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00513F10 -- 56 bytes, 14 instructions.
 *
 * addu $2,$4,$5 then lb $2,0x5($2) -- the +5 is folded into the load's
 * displacement, so the source index is a[i + 5].
 */

s32 insect_InsectTeamSlotIsFull_513f10(s8 *a)
{
    s32 i;

    for (i = 0; i < 5; i++) {
        if (a[i + 5] == -1) {
            return 0;
        }
    }
    return 1;
}
