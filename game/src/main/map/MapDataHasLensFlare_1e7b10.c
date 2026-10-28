/* rgp:protos */
#define RGP_SELF_MapDataHasLensFlare_1e7b10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Is bit 0x1 of the s32 at +0x28 set? */

typedef struct Obj_FUN_001e7b10 {
    u8 pad000[0x28];
    s32 flags;         /* +0x28 */
} Obj_FUN_001e7b10;

u8 MapDataHasLensFlare_1e7b10(Obj_FUN_001e7b10 *o)
{
    u8 set;

    set = (o->flags & 0x1) != 0;
    return set;
}
