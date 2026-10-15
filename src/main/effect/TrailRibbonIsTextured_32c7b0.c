#include "types.h"

/* Is bit 0x20000000 of the s32 at +0x18 set? */

typedef struct Obj_FUN_0032c7b0 {
    u8 pad000[0x18];
    s32 flags;         /* +0x18 */
} Obj_FUN_0032c7b0;

u8 TrailRibbonIsTextured_32c7b0(Obj_FUN_0032c7b0 *o)
{
    u8 set;

    set = (o->flags & 0x20000000) != 0;
    return set;
}
