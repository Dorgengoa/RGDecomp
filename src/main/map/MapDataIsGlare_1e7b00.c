#include "types.h"

/* Is bit 0x2 of the s32 at +0x28 set? */

typedef struct Obj_FUN_001e7b00 {
    u8 pad000[0x28];
    s32 flags;         /* +0x28 */
} Obj_FUN_001e7b00;

u8 MapDataIsGlare_1e7b00(Obj_FUN_001e7b00 *o)
{
    u8 set;

    set = (o->flags & 0x2) != 0;
    return set;
}
