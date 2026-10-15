#include "types.h"
/* insect 0x5138B0 -- 8 B / 2 words.  `jr $31 / lw $2, 0x988($4)`:
 * a bare word accessor.  The load WIDTH (lw) fixes the member at s32. */

typedef struct Obj {
    u8  pad00[0x988];
    s32 m988;                 /* +0x988 */
} Obj;

s32 insect_InsectTeamGetName_5138b0(Obj *o)
{
    return o->m988;
}
