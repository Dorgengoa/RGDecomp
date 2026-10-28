/* rgp:protos */
#define RGP_SELF_AiIsNoTimeout_2c1230 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Is bit 0x8 of the s32 at +0x294 set? */

typedef struct Obj_FUN_002c1230 {
    u8 pad000[0x294];
    s32 flags;         /* +0x294 */
} Obj_FUN_002c1230;

u8 AiIsNoTimeout_2c1230(Obj_FUN_002c1230 *o)
{
    u8 set;

    set = (o->flags & 0x8) != 0;
    return set;
}
