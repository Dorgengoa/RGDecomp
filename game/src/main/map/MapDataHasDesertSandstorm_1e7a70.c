/* rgp:protos */
#define RGP_SELF_MapDataHasDesertSandstorm_1e7a70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Is bit 0x800 of the s32 at +0x28 set? */

typedef struct Obj_FUN_001e7a70 {
    u8 pad000[0x28];
    s32 flags;         /* +0x28 */
} Obj_FUN_001e7a70;

u8 MapDataHasDesertSandstorm_1e7a70(Obj_FUN_001e7a70 *o)
{
    u8 set;

    set = (o->flags & 0x800) != 0;
    return set;
}
