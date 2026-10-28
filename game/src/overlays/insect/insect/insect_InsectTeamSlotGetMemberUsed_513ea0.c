/* rgp:protos */
#define RGP_SELF_insect_InsectTeamSlotGetMemberUsed_513ea0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x513EA0 -- 12 B / 3 words.  `addu` then `lb 0x5($2)`: a
 * SIGNED byte-array subscript.  The addu's operand order tracks the folded
 * displacement -- base in rt when the offset is non-zero (0x00513EA0), base in
 * rs when it is zero (0x00513F50) -- so both are the same source spelling. */

typedef struct Obj {
    u8 pad00[0x5];
    s8 m05[4];               /* +0x5 */
} Obj;

s8 insect_InsectTeamSlotGetMemberUsed_513ea0(Obj *o, s32 i)
{
    return o->m05[i];
}
