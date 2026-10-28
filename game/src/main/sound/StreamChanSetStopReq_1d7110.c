/* rgp:protos */
#define RGP_SELF_StreamChanSetStopReq_1d7110 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Clear flag 0x8, then set it again if the second argument says
   so.  Proven at StreamChanSetRestoreResumeReq_1d7080. */

typedef struct Obj_FUN_001d7110 {
    u8 pad000[0x94];
    s32 flags;         /* +0x94 */
} Obj_FUN_001d7110;

void StreamChanSetStopReq_1d7110(Obj_FUN_001d7110 *o, s32 on)
{
    o->flags = o->flags & -9;
    if (on != 0) {
        o->flags = o->flags | 0x8;
    }
}
