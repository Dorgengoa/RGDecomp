/* rgp:protos */
#define RGP_SELF_insect_InsectSeqGetSubState_4ea330 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x4EA330 -- 8 B / 2 words.  `jr $31 / lw $2, 0x28($4)`:
 * a bare word accessor.  The load WIDTH (lw) fixes the member at s32. */

typedef struct Obj {
    u8  pad00[0x28];
    s32 m28;                 /* +0x28 */
} Obj;

s32 insect_InsectSeqGetSubState_4ea330(Obj *o)
{
    return o->m28;
}
