/* rgp:protos */
#define RGP_SELF_MapDataIsNoDarken_1e7aa0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Is bit 0x80 of the s32 at +0x28 set? */

typedef struct Obj_FUN_001e7aa0 {
    u8 pad000[0x28];
    s32 flags;         /* +0x28 */
} Obj_FUN_001e7aa0;

u8 MapDataIsNoDarken_1e7aa0(Obj_FUN_001e7aa0 *o)
{
    u8 set;

    set = (o->flags & 0x80) != 0;
    return set;
}
