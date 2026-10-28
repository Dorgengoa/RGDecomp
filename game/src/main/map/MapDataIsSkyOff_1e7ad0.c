/* rgp:protos */
#define RGP_SELF_MapDataIsSkyOff_1e7ad0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Is bit 0x10 of the s32 at +0x28 set? */

typedef struct Obj_FUN_001e7ad0 {
    u8 pad000[0x28];
    s32 flags;         /* +0x28 */
} Obj_FUN_001e7ad0;

u8 MapDataIsSkyOff_1e7ad0(Obj_FUN_001e7ad0 *o)
{
    u8 set;

    set = (o->flags & 0x10) != 0;
    return set;
}
