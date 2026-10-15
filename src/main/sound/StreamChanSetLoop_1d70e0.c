#include "types.h"

/* Clear flag 0x10, then set it again if the second argument says
   so.  Proven at StreamChanSetRestoreResumeReq_1d7080. */

typedef struct Obj_FUN_001d70e0 {
    u8 pad000[0x94];
    s32 flags;         /* +0x94 */
} Obj_FUN_001d70e0;

void StreamChanSetLoop_1d70e0(Obj_FUN_001d70e0 *o, s32 on)
{
    o->flags = o->flags & -0x11;
    if (on != 0) {
        o->flags = o->flags | 0x10;
    }
}
