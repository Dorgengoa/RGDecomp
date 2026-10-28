/* rgp:protos */
#define RGP_SELF_StreamChanIsPauseReq_1d7270 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Is bit 0x4 of the s32 at +0x94 set? */

typedef struct Obj_FUN_001d7270 {
    u8 pad000[0x94];
    s32 flags;         /* +0x94 */
} Obj_FUN_001d7270;

u8 StreamChanIsPauseReq_1d7270(Obj_FUN_001d7270 *o)
{
    u8 set;

    set = (o->flags & 0x4) != 0;
    return set;
}
