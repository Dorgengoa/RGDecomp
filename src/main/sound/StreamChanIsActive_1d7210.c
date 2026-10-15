#include "types.h"

/* Is bit 0x10000 of the s32 at +0x94 set? */

typedef struct Obj_FUN_001d7210 {
    u8 pad000[0x94];
    s32 flags;         /* +0x94 */
} Obj_FUN_001d7210;

u8 StreamChanIsActive_1d7210(Obj_FUN_001d7210 *o)
{
    u8 set;

    set = (o->flags & 0x10000) != 0;
    return set;
}
