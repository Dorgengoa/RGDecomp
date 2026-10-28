/* rgp:protos */
#define RGP_SELF_MapDataIsHidden_1e7c10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Is bit 0x1 of the u8 at +0x24 set? */

typedef struct Obj_FUN_001e7c10 {
    u8 pad000[0x24];
    u8 flags;         /* +0x24 */
} Obj_FUN_001e7c10;

u8 MapDataIsHidden_1e7c10(Obj_FUN_001e7c10 *o)
{
    u8 set;

    set = (o->flags & 0x1) != 0;
    return set;
}
