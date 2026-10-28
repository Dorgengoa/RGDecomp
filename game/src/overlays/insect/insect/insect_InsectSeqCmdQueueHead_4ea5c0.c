/* rgp:protos */
#define RGP_SELF_insect_InsectSeqCmdQueueHead_4ea5c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x4EA5C0 -- 8 B / 2 words.  `jr $31 / lw $2, 0x5C($4)`:
 * a bare word accessor.  The load WIDTH (lw) fixes the member at s32. */

typedef struct Obj {
    u8  pad00[0x5C];
    s32 m5C;                 /* +0x5C */
} Obj;

s32 insect_InsectSeqCmdQueueHead_4ea5c0(Obj *o)
{
    return o->m5C;
}
