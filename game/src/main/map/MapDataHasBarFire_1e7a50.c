/* rgp:protos */
#define RGP_SELF_MapDataHasBarFire_1e7a50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Is bit 0x2000 of the s32 at +0x28 set? */

typedef struct Obj_FUN_001e7a50 {
    u8 pad000[0x28];
    s32 flags;         /* +0x28 */
} Obj_FUN_001e7a50;

u8 MapDataHasBarFire_1e7a50(Obj_FUN_001e7a50 *o)
{
    u8 set;

    set = (o->flags & 0x2000) != 0;
    return set;
}
