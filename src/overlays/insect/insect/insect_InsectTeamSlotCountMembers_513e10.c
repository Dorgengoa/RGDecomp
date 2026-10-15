#include "types.h"
/* insect 0x00513E10 -- 104 bytes, 26 instructions.  Counts the occupied slots
 * of a five-entry table.  The counter is declared BEFORE the index so it takes
 * $17 and the index $16. */

extern s32 insect_InsectTeamSlotGetMember_513eb0(void *o, s32 i);

s32 insect_InsectTeamSlotCountMembers_513e10(void *o)
{
    s32 n;
    s32 i;

    n = 0;
    for (i = 0; i < 5; i++) {
        if (insect_InsectTeamSlotGetMember_513eb0(o, i) != -1) {
            n++;
        }
    }
    return n;
}
