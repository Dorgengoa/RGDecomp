#include "types.h"
/* insect 0x00513F60 -- 52 bytes.  Linear search of a five-byte table. */

s32 insect_InsectTeamSlotFindMember_513f60(s8 *t, s32 v)
{
    s32 i;

    for (i = 0; i < 5; i++) {
        if (v == t[i]) {
            return i;
        }
    }
    return -1;
}
