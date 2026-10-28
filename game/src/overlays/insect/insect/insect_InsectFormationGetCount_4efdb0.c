/* rgp:protos */
#define RGP_SELF_insect_InsectFormationGetCount_4efdb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x4EFDB0 -- 8 B / 2 words.  `jr $31 / lw $2, 0x8($4)`:
 * a bare word accessor.  The load WIDTH (lw) fixes the member at s32. */

typedef struct Obj {
    u8  pad00[0x8];
    s32 m08;                 /* +0x8 */
} Obj;

s32 insect_InsectFormationGetCount_4efdb0(Obj *o)
{
    return o->m08;
}
