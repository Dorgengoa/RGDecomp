/* rgp:protos */
#define RGP_SELF_MapDataHasKujeSky_1e7a60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Is bit 0x1000 of the s32 at +0x28 set? */

typedef struct Obj_FUN_001e7a60 {
    u8 pad000[0x28];
    s32 flags;         /* +0x28 */
} Obj_FUN_001e7a60;

u8 MapDataHasKujeSky_1e7a60(Obj_FUN_001e7a60 *o)
{
    u8 set;

    set = (o->flags & 0x1000) != 0;
    return set;
}
