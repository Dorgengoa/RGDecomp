#include "types.h"

/* Is bit 0x100 of the s32 at +0x28 set? */

typedef struct Obj_FUN_001e7a90 {
    u8 pad000[0x28];
    s32 flags;         /* +0x28 */
} Obj_FUN_001e7a90;

u8 MapDataIsJasterOnly_1e7a90(Obj_FUN_001e7a90 *o)
{
    u8 set;

    set = (o->flags & 0x100) != 0;
    return set;
}
