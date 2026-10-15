#include "types.h"

/* Is bit 0x8 of the s32 at +0x28 set? */

typedef struct Obj_FUN_001e7ae0 {
    u8 pad000[0x28];
    s32 flags;         /* +0x28 */
} Obj_FUN_001e7ae0;

u8 MapDataIsWindOff_1e7ae0(Obj_FUN_001e7ae0 *o)
{
    u8 set;

    set = (o->flags & 0x8) != 0;
    return set;
}
