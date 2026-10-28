/* rgp:protos */
#define RGP_SELF_StreamChanIsRestoreResumeReq_1d7230 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Is bit 0x40 of the s32 at +0x94 set? */

typedef struct Obj_FUN_001d7230 {
    u8 pad000[0x94];
    s32 flags;         /* +0x94 */
} Obj_FUN_001d7230;

u8 StreamChanIsRestoreResumeReq_1d7230(Obj_FUN_001d7230 *o)
{
    u8 set;

    set = (o->flags & 0x40) != 0;
    return set;
}
