#include "types.h"

/* Address of the sub-object at +0xD0. */

typedef struct Obj_FUN_00352960 {
    u8 pad000[0xD0];
    u8 sub[1];         /* +0xD0 */
} Obj_FUN_00352960;

void *EvTargetGetPoints_352960(Obj_FUN_00352960 *o)
{
    return o->sub;
}
