#include "types.h"
/* insect 0x513E00 -- 8 B / 2 words.  `jr $31 / lw $2, 0x1C($4)`:
 * a bare word accessor.  The load WIDTH (lw) fixes the member at s32. */

typedef struct Obj {
    u8  pad00[0x1C];
    s32 m1C;                 /* +0x1C */
} Obj;

s32 insect_InsectTeamSlotGetName_513e00(Obj *o)
{
    return o->m1C;
}
