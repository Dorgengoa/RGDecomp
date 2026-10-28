/* rgp:protos */
#define RGP_SELF_MapDataIsGenericMap_1e7ac0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Is bit 0x20 of the s32 at +0x28 set? */

typedef struct Obj_FUN_001e7ac0 {
    u8 pad000[0x28];
    s32 flags;         /* +0x28 */
} Obj_FUN_001e7ac0;

u8 MapDataIsGenericMap_1e7ac0(Obj_FUN_001e7ac0 *o)
{
    u8 set;

    set = (o->flags & 0x20) != 0;
    return set;
}
