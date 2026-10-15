#include "types.h"

/* Is bit 0x20000 of the s32 at +0x94 set? */

typedef struct Obj_FUN_001d71f0 {
    u8 pad000[0x94];
    s32 flags;         /* +0x94 */
} Obj_FUN_001d71f0;

u8 StreamChanIsPlaying_1d71f0(Obj_FUN_001d71f0 *o)
{
    u8 set;

    set = (o->flags & 0x20000) != 0;
    return set;
}
