/* rgp:protos */
#define RGP_SELF_MapDataHasSkyParts_1e7ab0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Is bit 0x40 of the s32 at +0x28 set? */

typedef struct Obj_FUN_001e7ab0 {
    u8 pad000[0x28];
    s32 flags;         /* +0x28 */
} Obj_FUN_001e7ab0;

u8 MapDataHasSkyParts_1e7ab0(Obj_FUN_001e7ab0 *o)
{
    u8 set;

    set = (o->flags & 0x40) != 0;
    return set;
}
