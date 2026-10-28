/* rgp:protos */
#define RGP_SELF_StreamChanSetRestoreResumeReq_1d7080 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Clear flag 0x40, then set it again if the second argument says so. */

typedef struct Obj_FUN_001d7080 {
    u8 pad000[0x94];
    s32 flags;         /* +0x94 */
} Obj_FUN_001d7080;

void StreamChanSetRestoreResumeReq_1d7080(Obj_FUN_001d7080 *o, s32 on)
{
    o->flags = o->flags & -0x41;
    if (on != 0) {
        o->flags = o->flags | 0x40;
    }
}
