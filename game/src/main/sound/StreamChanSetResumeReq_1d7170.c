/* rgp:protos */
#define RGP_SELF_StreamChanSetResumeReq_1d7170 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Clear flag 0x2, then set it again if the second argument says
   so.  Proven at StreamChanSetRestoreResumeReq_1d7080. */

typedef struct Obj_FUN_001d7170 {
    u8 pad000[0x94];
    s32 flags;         /* +0x94 */
} Obj_FUN_001d7170;

void StreamChanSetResumeReq_1d7170(Obj_FUN_001d7170 *o, s32 on)
{
    o->flags = o->flags & -3;
    if (on != 0) {
        o->flags = o->flags | 0x2;
    }
}
