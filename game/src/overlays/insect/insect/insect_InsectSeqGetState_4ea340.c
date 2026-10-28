/* rgp:protos */
#define RGP_SELF_insect_InsectSeqGetState_4ea340 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x4EA340 -- 8 B / 2 words.  `jr $31 / lw $2, 0x24($4)`:
 * a bare word accessor.  The load WIDTH (lw) fixes the member at s32. */

typedef struct Obj {
    u8  pad00[0x24];
    s32 m24;                 /* +0x24 */
} Obj;

s32 insect_InsectSeqGetState_4ea340(Obj *o)
{
    return o->m24;
}
