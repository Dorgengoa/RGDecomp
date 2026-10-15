#include "types.h"

/* Address of the sub-object at +0xE0. */

typedef struct Obj_FUN_00303b20 {
    u8 pad000[0xE0];
    u8 sub[1];         /* +0xE0 */
} Obj_FUN_00303b20;

void *EvDoorObjGetCursor_303b20(Obj_FUN_00303b20 *o)
{
    return o->sub;
}
