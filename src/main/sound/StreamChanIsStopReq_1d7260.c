#include "types.h"

/* Is bit 0x8 of the s32 at +0x94 set? */

typedef struct Obj_FUN_001d7260 {
    u8 pad000[0x94];
    s32 flags;         /* +0x94 */
} Obj_FUN_001d7260;

u8 StreamChanIsStopReq_1d7260(Obj_FUN_001d7260 *o)
{
    u8 set;

    set = (o->flags & 0x8) != 0;
    return set;
}
