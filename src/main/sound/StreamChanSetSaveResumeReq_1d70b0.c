#include "types.h"

/* Clear flag 0x20, then set it again if the second argument says
   so.  Proven at StreamChanSetRestoreResumeReq_1d7080. */

typedef struct Obj_FUN_001d70b0 {
    u8 pad000[0x94];
    s32 flags;         /* +0x94 */
} Obj_FUN_001d70b0;

void StreamChanSetSaveResumeReq_1d70b0(Obj_FUN_001d70b0 *o, s32 on)
{
    o->flags = o->flags & -0x21;
    if (on != 0) {
        o->flags = o->flags | 0x20;
    }
}
