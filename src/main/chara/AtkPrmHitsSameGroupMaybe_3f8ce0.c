#include "types.h"

/* Is bit 0x40000000 of the s32 at +0x10 set? */

typedef struct Obj_FUN_003f8ce0 {
    u8 pad000[0x10];
    s32 flags;         /* +0x10 */
} Obj_FUN_003f8ce0;

u8 AtkPrmHitsSameGroupMaybe_3f8ce0(Obj_FUN_003f8ce0 *o)
{
    u8 set;

    set = (o->flags & 0x40000000) != 0;
    return set;
}
