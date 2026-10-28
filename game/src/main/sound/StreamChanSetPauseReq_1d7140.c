/* rgp:protos */
#define RGP_SELF_StreamChanSetPauseReq_1d7140 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Clear flag 0x4, then set it again if the second argument says
   so.  Proven at StreamChanSetRestoreResumeReq_1d7080. */

typedef struct Obj_FUN_001d7140 {
    u8 pad000[0x94];
    s32 flags;         /* +0x94 */
} Obj_FUN_001d7140;

void StreamChanSetPauseReq_1d7140(Obj_FUN_001d7140 *o, s32 on)
{
    o->flags = o->flags & -5;
    if (on != 0) {
        o->flags = o->flags | 0x4;
    }
}
