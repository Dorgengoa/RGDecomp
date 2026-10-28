/* rgp:protos */
#define RGP_SELF_AiIsMoveTimedOut_2c1240 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Is bit 0x1 of the s32 at +0x294 set? */

typedef struct Obj_FUN_002c1240 {
    u8 pad000[0x294];
    s32 flags;         /* +0x294 */
} Obj_FUN_002c1240;

u8 AiIsMoveTimedOut_2c1240(Obj_FUN_002c1240 *o)
{
    u8 set;

    set = (o->flags & 0x1) != 0;
    return set;
}
