#include "types.h"
/* insect 0x00514190 -- 29 instructions.  A five-slot linear scan for the
 * first free entry; -1 stays live in $5 across the whole loop, so it is one
 * comparison constant and not two literals.
 *
 * The +5 address is materialised into $3 in the `bne` delay slot while the
 * TEST of the same byte folds +5 into its displacement -- two pointer locals,
 * exactly as 00512CD0. */

extern s32 insect_InsectTeamSlotFindMember_513f60(void);

s32 insect_InsectTeamSlotAddMember_514190(s8 *base, s8 val)
{
    s32 i;
    s8 *e;
    s8 *q;

    if (insect_InsectTeamSlotFindMember_513f60() != -1) {
        return 0;
    }
    for (i = 0; i < 5; i++) {
        e = base + i;
        q = e + 5;
        if (e[5] == -1) {
            e[0] = val;
            *q = 1;
            return 1;
        }
    }
    return 0;
}
