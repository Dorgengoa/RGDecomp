/* rgp:protos */
#define RGP_SELF_StreamChanIsOpenReq_1d7290 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Is bit 0x1 of the s32 at +0x94 set? */

typedef struct Obj_FUN_001d7290 {
    u8 pad000[0x94];
    s32 flags;         /* +0x94 */
} Obj_FUN_001d7290;

u8 StreamChanIsOpenReq_1d7290(Obj_FUN_001d7290 *o)
{
    u8 set;

    set = (o->flags & 0x1) != 0;
    return set;
}
