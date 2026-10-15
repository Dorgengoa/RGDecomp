#include "types.h"
/* insect 0x51CEE0 -- 8 B / 2 words.  `jr $31 / lw $2, 0x8C($4)`:
 * a bare word accessor.  The load WIDTH (lw) fixes the member at s32. */

typedef struct Obj {
    u8  pad00[0x8C];
    s32 m8C;                 /* +0x8C */
} Obj;

s32 insect_InsectAbilityTableGetMatchCount_51cee0(Obj *o)
{
    return o->m8C;
}
