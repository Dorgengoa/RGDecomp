/* rgp:protos */
#define RGP_SELF_MapDataIsGenericTransporter_1e7a80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Is bit 0x200 of the s32 at +0x28 set? */

typedef struct Obj_FUN_001e7a80 {
    u8 pad000[0x28];
    s32 flags;         /* +0x28 */
} Obj_FUN_001e7a80;

u8 MapDataIsGenericTransporter_1e7a80(Obj_FUN_001e7a80 *o)
{
    u8 set;

    set = (o->flags & 0x200) != 0;
    return set;
}
