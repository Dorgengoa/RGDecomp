#include "types.h"

/* Clear flag 0x1, then set it again if the second argument says
   so.  Proven at StreamChanSetRestoreResumeReq_1d7080. */

typedef struct Obj_FUN_002c1200 {
    u8 pad000[0x294];
    s32 flags;         /* +0x294 */
} Obj_FUN_002c1200;

void AiSetMoveTimedOut_2c1200(Obj_FUN_002c1200 *o, s32 on)
{
    o->flags = o->flags & -2;
    if (on != 0) {
        o->flags = o->flags | 0x1;
    }
}
