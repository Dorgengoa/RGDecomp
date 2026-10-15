#include "types.h"

/* Is bit 0x10 of the s32 at +0x94 set? */

typedef struct Obj_FUN_001d7250 {
    u8 pad000[0x94];
    s32 flags;         /* +0x94 */
} Obj_FUN_001d7250;

u8 StreamChanIsLoop_1d7250(Obj_FUN_001d7250 *o)
{
    u8 set;

    set = (o->flags & 0x10) != 0;
    return set;
}
