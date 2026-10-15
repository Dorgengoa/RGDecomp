#include "types.h"

/* Is bit 0x4 of the s32 at +0xA44 set? */

typedef struct Obj_FUN_00215000 {
    u8 pad000[0xA44];
    s32 flags;         /* +0xA44 */
} Obj_FUN_00215000;

u8 CharaFlagsA44TestRelated_215000(Obj_FUN_00215000 *o)
{
    u8 set;

    set = (o->flags & 0x4) != 0;
    return set;
}
