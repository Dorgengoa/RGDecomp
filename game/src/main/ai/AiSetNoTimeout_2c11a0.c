/* rgp:protos */
#define RGP_SELF_AiSetNoTimeout_2c11a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Clear flag 0x8, then set it again if the second argument says
   so.  Proven at StreamChanSetRestoreResumeReq_1d7080. */

typedef struct Obj_FUN_002c11a0 {
    u8 pad000[0x294];
    s32 flags;         /* +0x294 */
} Obj_FUN_002c11a0;

void AiSetNoTimeout_2c11a0(Obj_FUN_002c11a0 *o, s32 on)
{
    o->flags = o->flags & -9;
    if (on != 0) {
        o->flags = o->flags | 0x8;
    }
}
