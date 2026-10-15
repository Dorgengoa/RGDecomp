#include "types.h"

/* Clear flag 0x4, then set it again if the second argument says
   so.  Proven at StreamChanSetRestoreResumeReq_1d7080. */

typedef struct Obj_FUN_002c11d0 {
    u8 pad000[0x294];
    s32 flags;         /* +0x294 */
} Obj_FUN_002c11d0;

void AiSetTargetMissing_2c11d0(Obj_FUN_002c11d0 *o, s32 on)
{
    o->flags = o->flags & -5;
    if (on != 0) {
        o->flags = o->flags | 0x4;
    }
}
