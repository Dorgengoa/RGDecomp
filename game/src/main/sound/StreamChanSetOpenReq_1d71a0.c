/* rgp:protos */
#define RGP_SELF_StreamChanSetOpenReq_1d71a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Clear flag 0x1, then set it again if the second argument says
   so.  Proven at StreamChanSetRestoreResumeReq_1d7080. */

typedef struct Obj_FUN_001d71a0 {
    u8 pad000[0x94];
    s32 flags;         /* +0x94 */
} Obj_FUN_001d71a0;

void StreamChanSetOpenReq_1d71a0(Obj_FUN_001d71a0 *o, s32 on)
{
    o->flags = o->flags & -2;
    if (on != 0) {
        o->flags = o->flags | 0x1;
    }
}
