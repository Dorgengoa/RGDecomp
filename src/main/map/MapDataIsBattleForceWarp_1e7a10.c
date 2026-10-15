#include "types.h"

/* Is bit 0x10000 of the s32 at +0x28 set? */

typedef struct Obj_FUN_001e7a10 {
    u8 pad000[0x28];
    s32 flags;         /* +0x28 */
} Obj_FUN_001e7a10;

u8 MapDataIsBattleForceWarp_1e7a10(Obj_FUN_001e7a10 *o)
{
    u8 set;

    set = (o->flags & 0x10000) != 0;
    return set;
}
