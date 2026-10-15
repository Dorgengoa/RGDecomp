#include "types.h"
/* insect 0x50DB30 -- 8 B / 2 words.  `jr $31 / lw $2, 0x5B18($4)`:
 * a bare word accessor.  The load WIDTH (lw) fixes the member at s32. */

typedef struct Obj {
    u8  pad00[0x5B18];
    s32 m5B18;                 /* +0x5B18 */
} Obj;

s32 insect_InsectBattleGetSpecialRec_50db30(Obj *o)
{
    return o->m5B18;
}
