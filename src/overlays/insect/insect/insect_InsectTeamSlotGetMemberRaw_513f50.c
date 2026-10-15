#include "types.h"
/* insect 0x513F50 -- 12 B / 3 words.  `addu` then `lb 0x0($2)`: a
 * SIGNED byte-array subscript.  The addu's operand order tracks the folded
 * displacement -- base in rt when the offset is non-zero (0x00513EA0), base in
 * rs when it is zero (0x00513F50) -- so both are the same source spelling. */

typedef struct Obj {
    s8 m00[4];               /* +0x0 */
} Obj;

s8 insect_InsectTeamSlotGetMemberRaw_513f50(Obj *o, s32 i)
{
    return o->m00[i];
}
