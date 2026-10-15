#include "types.h"

/* Is bit 0x1 of the u8 at +0x23 set? */

typedef struct Obj_FUN_001e7c20 {
    u8 pad000[0x23];
    u8 flags;         /* +0x23 */
} Obj_FUN_001e7c20;

u8 MapDataIsEnabled_1e7c20(Obj_FUN_001e7c20 *o)
{
    u8 set;

    set = (o->flags & 0x1) != 0;
    return set;
}
